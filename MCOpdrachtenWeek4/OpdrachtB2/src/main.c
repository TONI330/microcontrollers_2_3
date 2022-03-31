#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

void adcInit(void)
{
	ADMUX = 0b01100001;
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;

	adcInit();

	while (1)
	{
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}