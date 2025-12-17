#include "stm32f446xx.h"
#include <stdint.h>
#include "tim2.h"

extern uint32_t tim2_isr_cntr;
void enable_interrupts(int irqn) {
	int reg = irqn / 32;
	int offset = irqn % 32;
	NVIC->ISER[reg] |= (1U << offset);
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~TIM2_SR_UIF;
	tim2_isr_cntr++;
}

