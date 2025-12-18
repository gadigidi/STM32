#include "seg7.h"
#include "timebase.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f446xx.h"

int main(void){

	timebase_init();

	seg7_init();

	seg7_update_buffer(0xABCD);


	//seg7_show_digit(1, 0xa);
	//seg7_show_digit(2, 1);
	//seg7_show_digit(3, 2);
	//seg7_show_digit(4, 3);
	//seg7_show_digit(1, 4);
	//seg7_show_digit(2, 5);
	//seg7_show_digit(3, 6);
	//seg7_show_digit(4, 7);
	//seg7_show_digit(1, 8);
	//seg7_show_digit(2, 9);

	while (1) {


    	//printf("conversion done. y_val = %d", y_val);

    }
}
