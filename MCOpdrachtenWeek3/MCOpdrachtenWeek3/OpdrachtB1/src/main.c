/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#define F_CPU 8e6
#include <asf.h>
#include "lcd.h"
#include <util/delay.h>
#include <stdio.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	_delay_ms(1500);
	init();
	
	/* Insert application code here, after the board has been initialized. */
	
	DDRA = 0xFF; //All A ports on output
	DDRD = 0x00; //All D ports on input
	
	TCCR2 = 0b00000111; //initialize counter on portd.7
	
	set_cursor(0);
	
	while(1==1) {
		PORTA = TCNT2;
		char test[16];
		sprintf(test, "Amount: %d", TCNT2);
		display_text(test);
		set_cursor(0);
		_delay_ms(100);
	}
}
	
