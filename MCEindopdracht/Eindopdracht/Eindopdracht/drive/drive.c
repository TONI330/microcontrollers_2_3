#include "drive.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define PWM_WAVE_TIME 20000
#define PERCENTAGE_DEAD_ZONE 5
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define REVERSED_MOTOR LEFT_MOTOR

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

int calculate_timer_compare_time(int duty_cycle_ms)
{
	return PWM_WAVE_TIME - duty_cycle_ms;
}

void set_speed_motor(short percentage, short motor)
{
	// Reverse the percentage on the motor that is installed in reverse.
	percentage = motor == REVERSED_MOTOR ? percentage * -1 : percentage;
	
	if(motor == LEFT_MOTOR)
	{
		if(percentage > 0)
		{
			OCR1A = calculate_timer_compare_time(DRIVE_CLOCKWISE_FASTEST_MS + DRIVE_STEP_SIZE * percentage);	
		} 
		else
		{
			OCR1A = calculate_timer_compare_time(DRIVE_COUNTERCLOCKWISE_SLOWEST_MS + DRIVE_STEP_SIZE * percentage);
		}
	}
	
	if(motor == RIGHT_MOTOR)
	{
		if(percentage > 0)
		{
			OCR1B = calculate_timer_compare_time(DRIVE_CLOCKWISE_FASTEST_MS + DRIVE_STEP_SIZE * percentage);
		}
		else
		{
			OCR1B = calculate_timer_compare_time(DRIVE_COUNTERCLOCKWISE_SLOWEST_MS + DRIVE_STEP_SIZE * percentage);
		}
	}
	
	
	//if(motor == 0)
	//{
	//OCR1A = 20000 - (1300 + DRIVE_STEP_SIZE * percentage);
	//}
	//else
	//{
	//OCR1B = 20000 - (1300 + DRIVE_STEP_SIZE * percentage);
	//}
}

void set_speed(short percentage)
{
	set_speed_motor(percentage, LEFT_MOTOR);
	set_speed_motor(percentage, RIGHT_MOTOR);
}

void turn(short percentage)
{
	
}

void control_drive(short percentage_speed, short percentage_turn)
{
	// Make sure the values are within their bounds. i.e. -100 <= percentage_speed <= 100
	percentage_speed = percentage_speed > 100 ? 100 : percentage_speed;
	percentage_speed = percentage_speed < -100 ? -100 : percentage_speed;
	
	percentage_turn = percentage_turn > 100 ? 100 : percentage_turn;
	percentage_turn = percentage_turn < -100 ? -100 : percentage_turn;
	
	// If the speed is in the dead zone, set speed to 0.
	if(percentage_speed < PERCENTAGE_DEAD_ZONE && percentage_speed > PERCENTAGE_DEAD_ZONE * -1)
	{
		set_speed(0);
		turn(percentage_turn);
		return;
	}
	
	// If the turn is in the dead zone, set turn to 0.
	if(percentage_turn < PERCENTAGE_DEAD_ZONE && percentage_turn > PERCENTAGE_DEAD_ZONE * -1)
	{
		set_speed(percentage_speed);
		turn(0);
		return;
	}
	
	set_speed(percentage_speed);
	turn(percentage_turn);
}

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
	OCR1A = calculate_timer_compare_time(DRIVE_FULL_STOP_MS);
	OCR1B = calculate_timer_compare_time(DRIVE_FULL_STOP_MS);

	// Enable compare interrupts.
	TIMSK1 |= (1 << OCIE1A);
	TIMSK1 |= (1 << OCIE1B);
	
	DDRB |= (1 << 7) | (1 << 6);
}
