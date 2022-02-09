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


void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}



const unsigned char numbers[15] = {
	// dPgfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, //A
	0b01111100, //b
	0b00111001, //C
	0b01011110, //D
	0b01111001, //E
};




int index = 0;

void display(int digit) {
	if(0 <= digit && digit <= 15) {
		//display het getal
		PORTA = numbers[digit];
		} else {
		//display "e" van error
		PORTA = numbers[14];
	}
}

int main (void)
{
	DDRA = 0xFF; //All A ports on output
	DDRD = 0x00; //All D ports on input
	
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	while(1==1) {
		display(index);
	}
}

ISR (INT1_vect) {
	if(index < 14) index++;
}

ISR (INT0_vect) {
	if(index >= -1) index--;
}




