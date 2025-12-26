#include "rfid.h"
#include "rc522.h"
#include "gpio.h"
#include "isr.h"
#include "timebase.h"
#include "spi.h"
#include "seg7.h"

#include "stm32f446xx.h"
#include <stdint.h>
#include <stdbool.h>

void rfid_init(void) {
    gpio_init(GPIOAEN);

    rfid_hw_init();

    rc522_init();

    //Enable interrupts from RFID_IRQ
    //rfid_enable_irq();

    rfid_spi1_config();
}

void rfid_enable_irq(void) {
    //Enable clock for EXTI configurations
    RCC->APB2ENR |= (1U << 14);
    //Select GPIOA as IRQ source for EXTI1, because the RC522 IRQ connected to PA1
    SYSCFG->EXTICR[0] &= ~(0xFU << 3);
    //Clear mask for EXTI line 1
    EXTI->IMR |= (1U << 1);
    //Config IRQ sensetivity = active low (falling_dege only)
    EXTI->RTSR &= ~(1U << 1);
    EXTI->FTSR |= (1U << 1);

    //Clean old PR before anabling
    EXTI->PR = (1U << 1);

    isr_enable_interrupts(EXTI1_IRQn);
}

void rfid_spi1_config(void) {
    spi1_init();
    spi1_enable_clock();
    spi1_config_baudrate(SPI_BR_DIV64);
    spi1_config_mode(SPI_MASTER);
    spi1_config_clock_mode(SPI_MODE_0);
    spi1_config_bit_order(SPI_MSB_FIRST);
    spi1_config_nss(SPI_NSS_SOFTWARE);
    spi1_config_data_size(SPI_DATASIZE_8BIT);
    spi1_enable(1U);
}

static volatile bool rfid_pending_irq = 0;
void rfid_update_irq_flag(void) {
    rfid_pending_irq = 1;
}

bool rfid_show_pending_irq_status(void) {
    return rfid_pending_irq;
}

typedef enum {
    RFID_IDLE, RFID_WAIT_IRQ, RFID_READ_UID, RFID_SHOW_UID, RFID_ERROR
} rfid_state_t;

void rfid_fsm(void) {
    static rfid_state_t rfid_state = RFID_IDLE; //Check later where to put
    static uint8_t uid[];
    int len;
    uint8_t cascade_level;
    static bool error_detected = 0;

    //Non blocking delays
    static idle_start_time = 0;
    static req_timeout_start_time = 0;
    static uid_timeout_start_time = 0;
    static cooldown_start_time = 0;
    uint32_t time_now;

    switch (rfid_state) {
    case RFID_IDLE:
        time_now = timebase_show_ms();
        uint32_t delta_time = time_now - idle_start_time;
        if (delta_time >= RFID_POLL_PERIOD_MS) {
            rc522_clean_flags(); //TODO
            rfid_pending_req = 0; //Just to be sure before waiting for new irq
            rfid_send_req(); //TODO
            rfid_state = RFID_WAIT_IRQ;
        }
        break;
    case RFID_WAIT_IRQ:
        if (rfid_pending_irq) {
            rc522_read_(); //TODO
            rfid_state = RFID_READ_UID;
            rfid_pending_irq = 0;
        }
        break;
    case RFID_READ_UID:
        if (error_detected) {
            rfid_state = RFID_IDLE;
        }
        else {
            rfid_state = RFID_SHOW_UID;
        }
        break;
    case RFID_SHOW_UID:
        seg7_set_buffer_for_scroll(uid);
        rfid_state = RFID_ERROR;
        break;
    case RFID_ERROR:
        rfid_error(); //TODO
        rfid_state = RFID_IDLE;
    }
}

