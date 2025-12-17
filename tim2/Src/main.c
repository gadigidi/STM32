#include "tim2.h"
#include <stdint.h>
#include "stm32f446xx.h"

volatile uint32_t tim2_isr_cntr;
int main(void){

	tim2_init();

	tim2_enable_interrupt();
	
	tim2_enable();
	
	volatile uint32_t j;
	//volatile int i;
	while (1) {
		/*//wait ~1s
		for (i = 0; i < 16000000; i++) {
		 }*/
		j++;
	}
}
