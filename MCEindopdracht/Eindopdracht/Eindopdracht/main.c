#define F_CPU 16e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Drive/drive.h"
#include "PwmReader/pwmReader.h"

#define STICK_RIGHT_UP_DOWN 2
#define STICK_RIGHT_LEFT_RIGHT 0
#define STICK_LEFT_UP_DOWN 3
#define STICK_LEFT_LEFT_RIGHT 1

#define STICK_MINIMUM 450
#define STICK_CENTER 670
#define STICK_MAXIMUM 890

int calculate_stick_percentage(int pwm_value, int delta)
{
	if(STICK_MINIMUM >= pwm_value - delta) return 0;
	if(STICK_MAXIMUM <= pwm_value + delta) return 100;
	if(STICK_CENTER <= pwm_value + delta && STICK_CENTER >= pwm_value - delta) return 50;
	
	return (pwm_value - STICK_MINIMUM) / 440.0 * 100;
}

int main(void)
{
	sei(); // Enable interrupts.
	DDRB = 0;
	
	init_servos();
	init_pwm();
	
	int* test_value = malloc(16);
	pwm_reader_add_pin(STICK_LEFT_UP_DOWN, test_value);

    while (1) 
    {
		control_drive(100 - calculate_stick_percentage(*test_value, 10), 0);
    }
}
