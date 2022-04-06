#include "drive.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void init_servos()
{
	// Set up timer in PWM, Phase and frequency Correct mode.
	TCCR1A = 0b01010110;

	// Set up timer with pre-scaler = 8 and PWM, Phase and frequency correct mode.
	TCCR1B |= (1 << WGM13) | (1 << CS11);

	// Initialize counter.
	TCNT1 = 0;
	ICR1 = 20000;

	// Initialize compare values.
	OCR1A = 20000 - DRIVE_FULL_STOP_MS;
	OCR1B = 20000 - DRIVE_FULL_STOP_MS;

	// Enable compare interrupts.
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
	
	DDRB |= (1 << 7) | (1 << 6);
}

// Interrupt for pin 13.
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << 7);
}

// Interrupt for pin 12.
ISR(TIMER1_COMPB_vect)
{
	PORTB ^= (1 << 6);
}

void control_drive(short percentage_speed, short percentage_turn)
{
	
}

void set_speed(short percentage, short motor)
{	
	if(motor == 0) 
	{
		OCR1A = 20000 - (1300 + DRIVE_STEP_SIZE * percentage);
	}
	else
	{
		OCR1B = 20000 - (1300 + DRIVE_STEP_SIZE * percentage);
	}
}
