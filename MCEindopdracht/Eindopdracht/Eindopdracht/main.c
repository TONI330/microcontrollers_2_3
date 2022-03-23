/*
 * Eindopdracht.c
 *
 * Created: 23/03/2022 12:23:13
 * Author : tjtle
 */

#define F_CPU 16e6

#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	
	TCCR2 = 0b00000111; //initialize counter on portd.7

	
    while (1) 
    {
		OCR1A++;
		if(OCR1A > 1550) OCR1A = 1350;
		_delay_ms(100); 
    }
}

