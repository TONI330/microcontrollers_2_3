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

#include <avr/io.h>
#include <util/delay.h>

typedef struct 
{
	unsigned char adress;
	unsigned int delayms ;
} LIGHTS_PATTERN;

LIGHTS_PATTERN pattern[] = 
{
	{0xFF, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0x00,  50}, {0xFF,  50},
	{0x00,  50}, {0xFF,  50},
	{0x00,  50}, {0xFF,  50},
			{0xFF, 250},
	{0x00,  50}, {0xFF,  50},
	{0x00,  50}, {0xFF,  50},
	{0x00,  50}, {0xFF,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
};

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/*
main() loop, entry point of executable
*/
int main( void )
{
	DDRD = 0b11111111;					// PORTD all output
	
	//debug code
	int size = sizeof(pattern) / sizeof(LIGHTS_PATTERN);
	DDRC = 0xFF;
	PORTC = size;
	DDRA = 0xFF;
	
	while (1) {
		// Set index to begin of pattern array
		for(int i=0; i < sizeof(pattern) / sizeof(LIGHTS_PATTERN); i++)
		{
			PORTD = pattern[i].adress; //set light value
			wait(pattern[i].delayms); //wait the given delay
		}	
	}
	return 1;
}

