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
#include <util/delay.h>
#include "lookuppatterns.c"

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	/* Insert application code here, after the board has been initialized. */
	
	//DDRD = 0b10000000; 
	DDRD = 0b11111111;
	PORTD = 0xFF;
	
	while(1)
	{
		if(PINC & 0x01)
		{
			//laat led op PORTD7 knipperen
			PORTD = 0b10000000;
			wait(250);
			PORTD = 0x00;
			wait(250);

		} else
		{
			PORTD = 0x00;
		}	
	}
	

	
	return 1;
}
