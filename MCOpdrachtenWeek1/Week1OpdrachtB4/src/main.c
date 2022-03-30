#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 1; // Turn first LED on.

	while (1)
	{
		wait(50);

		// If last LED is on than switch back to first LED.
		if (PORTB == (1 << 7))
		{
			PORTB = 1;
			continue;
		}

		PORTB = PORTB << 1; // Shift the active bit left one, turning on the next LED.
	}
}