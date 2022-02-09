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

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */


	/* Insert application code here, after the board has been initialized. */
	
	typedef enum state{fast=250, slow=1000};
	int currentSpeed = slow;
	
	DDRD = 0xFF;
	PORTD = 0xFF;
		
	int counter = 0;//incrementing value
	int countUp = 1;//bool to check if we're counting up or down
	
	while(1) 
	{
		
		
		if(PINC & 0x01 && currentSpeed == fast) 
		{
			currentSpeed = slow;
			counter = 0;
		} else if(PINC & 0X01 && currentSpeed == slow) 
		{
			currentSpeed = fast;
			counter = 0;
		}
		
		
		if(countUp == 1) {
			if(counter >= currentSpeed)
			{
				 countUp = 0;
				 PORTD = 0x80;
				 } else {
			counter++;
				}
			}
		if(countUp == 0)
		{
			if(counter <= 0)
			{
				countUp = 1;
				PORTD = 0X00;
			} else {
				counter--;
			}
		}		
		wait(1);
	}
	return 1;
}
