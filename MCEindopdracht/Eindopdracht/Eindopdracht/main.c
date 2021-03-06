#define F_CPU 16e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "Drive/drive.h"
#include "PwmReader/pwmReader.h"

// Sticks mapped to pins
#define STICK_RIGHT_VERTICAL 2
#define STICK_RIGHT_HORIZONTAL 0
#define STICK_LEFT_VERTICAL 3
#define STICK_LEFT_HORIZONTAL 1

#define STICK_MINIMUM 330
#define STICK_CENTER 550
#define STICK_MAXIMUM 770

/**
	Function to translate input pwm value to percentage from 0 to 100.
	@param delta is the deadzone used for minimum, maximum, and center.
*/
int calculate_stick_percentage(int pwm_value, int delta)
{
	if(STICK_MINIMUM >= pwm_value - delta) return 0;
	if(STICK_MAXIMUM <= pwm_value + delta) return 100;
	if(STICK_CENTER <= pwm_value + delta && STICK_CENTER >= pwm_value - delta) return 50;
	
	// Not max, not min, not center, so return percentage.
	return (pwm_value - STICK_MINIMUM) / 440.0 * 100;
}

int main(void)
{
	sei(); // Enable interrupts.
	DDRB = 0; // Initialize port to input to avoid frying receiver pins.
	
	init_servos();
	init_pwm(); 
	
	int* throttle_value = malloc(sizeof(int));
	int* steering_value = malloc(sizeof(int));
	
	pwm_reader_add_pin(STICK_LEFT_VERTICAL, throttle_value);
	pwm_reader_add_pin(STICK_RIGHT_HORIZONTAL, steering_value);

    while (1) 
    {
		control_drive(100 - calculate_stick_percentage(*throttle_value, 10), calculate_stick_percentage(*steering_value, 20));
    }
}
