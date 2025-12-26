#ifndef RC522_H_
#define RC522_H_

#include <stdint.h>
#include <stdbool.h>

#define RC522_WR            0
#define RC522_RD            1U
#define RC522_ADDR_MASK     0x7EU //b01111110 because lsb must be 0 and msb is wr/re

void rfid_ports_init(void);
void rfid_assert_reset(void);
void rfid_deassert_reset(void);
void rfid_assert_cs(void);
void rfid_deassert_cs(void);
void rc522_chip_init(void);
void rc522_hard_reset(void);
void rc522_write_reg(uint8_t addr, uint8_t data);
uint8_t rc522_read_reg(uint8_t addr);
void rc522_clean_flags(void);
void rc522_config_timeout(void);
void rc522_clean_fifo(void);

#endif /* RC522_H_ */
