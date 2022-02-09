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
#include <asf.h>

int main (void)
{
		// Init I/O
		DDRD = 0x00;			// PORTD(0:7) input
		DDRC = 0xFF;			// PORTC(0:7) output
		
		// Init Interrupt hardware
		EICRA |= 0x0B;			// INT1 falling edge, INT2 rising edge
		EIMSK |= 0x00000110;		// Enable INT1 & INT2
		
		// Enable global interrupt system
		//SREG = 0x80;			// Of direct via SREG of via wrapper
		sei();
		
		PORTC = 0x01; //turn on led on C0
		while (1) {} //do nothing
		return 1;
}

ISR (INT1_vect)
{
	//shift the led on forwards
	if(PORTC == 0x01) {
		PORTC = 0x80;
	} else PORTC >>= 1;
}

ISR (INT0_vect)
{
	//shift the led on backwards
	if(PORTC == 0x80) {
		PORTC = 0x01;
	} else PORTC <<= 1;
}
