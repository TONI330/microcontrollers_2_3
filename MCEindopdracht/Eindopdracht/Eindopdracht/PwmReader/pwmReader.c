#include "pwmReader.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define TICKS_PER_MEASUREMENT 10

typedef struct
{
	int* output_pointer;
	bool state;
} pwm_input_pin_t;

pwm_input_pin_t input_pins[8];

void init_pwm(void)
{
	 // Set up timer with pre-scaler = 8 and PWM, Phase and frequency correct mode.
	 TCCR0B |= (1 << WGM13) | (1 << CS11);

	 // Initialize counter.
	 TCNT0 = 0;

	 // Initialize compare values.
	 OCR0A = TICKS_PER_MEASUREMENT;

	 // Enable compare interrupts.
	 TIMSK0 |= (1 << OCIE0A);
}

void pwm_reader_add_pin(int pin, int* out_ticks)
{
	input_pins[pin].output_pointer = out_ticks;
	input_pins[pin].state = false;
}

/*
	Checks if a certain pin on port B is high.
	Param pin_number is the 0 indexed number of the pin 0-7.
	Returns true if the given pin is high, else false.
*/
bool pin_is_high(short pin_number)
{
	return PINB & (1 << pin_number);
}

ISR(TIMER0_COMPA_vect)
{
	for(int i = 0; i < 4; i++)
	{
		// If pin is not added, don't read it.
		if(input_pins[i].output_pointer == 0)
		{
			continue;
		}
		
		if(pin_is_high(i))
		{
			// Pin is high for first time this period.
			if(!input_pins[i].state)
			{
				input_pins[i].state = true; // Remember we've been high before, shouldn't keep resetting timer.
				*input_pins[i].output_pointer = 0; // Reset ticks.
			}
			
			// Pin has been high already.
			if(input_pins[i].state)
			{
				*input_pins[i].output_pointer += TICKS_PER_MEASUREMENT; // Add ticks to total ticks this period.
			}			
		}
		
		// Pin is low for the first time this period.
		if(!pin_is_high(i) && input_pins[i].state)
		{
			*input_pins[i].output_pointer += TICKS_PER_MEASUREMENT; // Add ticks to total ticks for the last time this period.
			input_pins[i].state = false; // Remember we've been low before, don't need to check again.
		}
	}
	
	TCNT0 = 0; // Reset internal timer so compare triggers again.
}
