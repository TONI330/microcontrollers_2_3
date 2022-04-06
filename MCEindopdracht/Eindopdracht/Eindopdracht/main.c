#define F_CPU 16e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Drive/drive.h"
#include "PwmReader/pwmReader.h"

void wait(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	sei(); // Enable interrupts.
	DDRB = 0;
	
	init_servos();
	init_pwm();
	
	int* test_value = malloc(16);
	pwm_reader_add_pin(3, test_value);

    while (1) 
    {
		set_speed((*test_value - 180) / 180.0 * 100, 0);
    }
}
