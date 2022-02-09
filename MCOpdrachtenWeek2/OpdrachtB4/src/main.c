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
#define F_CPU 8e6
#include <util/delay.h>

#define longDelay 250
#define mediumDelay 100
#define shortDelay 50

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

typedef struct {
	unsigned char data; //adress
	unsigned int delay; //time to wait in ms
} PATTERN_STRUCT;
	
PATTERN_STRUCT pattern[] = {
	{0b00000000, shortDelay}, {0b00000001, shortDelay}, {0b00100010, shortDelay}, {0b01000000, shortDelay},//g
	{0b00010100, shortDelay}, {0b00001000, shortDelay}, {0b00001001, shortDelay}
};

int main (void)
{	
	DDRA = 0xFF; //Set all A ports to output
	int index = 0;
	while(1==1) {
		//Display
		PORTA = pattern[index].data;
		//Wait
		wait(pattern[index].delay);
		//Set index
		if(index <= sizeof(pattern) / sizeof(PATTERN_STRUCT)) {
			index++;
		} else index = 0;
	}
	
}