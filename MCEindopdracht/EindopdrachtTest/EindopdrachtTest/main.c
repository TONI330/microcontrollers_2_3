/*
 * EindopdrachtTest.c
 *
 * Created: 14/03/2022 20:54:44
 * Author : tjtle
 */ 
#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>

#define TCONTROL 1520

int main(void)
{
	//DDRB = 1 << 7;
	//PORTB = 1 << 7;
	//while (1)
	//{
		//_delay_us(20000 - TCONTROL);
		//PORTB = 1 << 7;
		//_delay_us(TCONTROL);
		//PORTB = 0x00;
	//}
	
	#define INTERVAL 40000

	DDRB = 0xFF;
		
	OCR1A = INTERVAL / 4;
	ICR1 = INTERVAL;
	TCCR1A = 0b01010110;
	TCCR1B = 0b00011010;
	TCNT1 = 0x00;

	while(1)
	{

	}

}

