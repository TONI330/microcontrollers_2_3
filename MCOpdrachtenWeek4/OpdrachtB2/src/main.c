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
	ADMUX = 0b11100001;			// AREF=2,56 V, result left adjusted, channel3 at pin PF1
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;

	adcInit();

	while (1)
	{
		ADCSRA |= (1 << ADSC); //Start ADC conversion
		while ( ADCSRA & (1 << ADSC)) ;		// Wait for completion
		PORTA = ADCH;
		wait(10);
	}
}