#include "drive.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define PWM_WAVE_TIME 20000
#define PERCENTAGE_DEAD_ZONE 5
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define REVERSED_MOTOR RIGHT_MOTOR

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

bool is_same_value(int old_value, int new_value, int delta)
{
	return new_value < old_value + delta && new_value > old_value - delta;
}

void set_speed_motor(short percentage, short motor)
{	
	if(motor == LEFT_MOTOR)
	{
		if(percentage == 50)
		{
			OCR1B = calculate_timer_compare_time(DRIVE_FULL_STOP_MS);
			return;
		}
		
		if(percentage > 50)
		{
			OCR1B = calculate_timer_compare_time(DRIVE_COUNTERCLOCKWISE_SLOWEST_MS + DRIVE_STEP_SIZE * ((percentage - 50) / 50.0 * 100));
		} 
		else
		{
			OCR1B = calculate_timer_compare_time(DRIVE_CLOCKWISE_SLOWEST_MS - DRIVE_STEP_SIZE * ((50 - percentage) / 50.0 * 100));
		}
		
		return;
	}
	
	if(motor == RIGHT_MOTOR)
	{
		if(percentage == 50)
		{
			OCR1A = calculate_timer_compare_time(DRIVE_FULL_STOP_MS);
			return;
		}
		
		if(percentage > 50)
		{
			OCR1A = calculate_timer_compare_time(DRIVE_CLOCKWISE_SLOWEST_MS - DRIVE_STEP_SIZE * ((percentage - 50) / 50.0 * 100));
		}
		else
		{
			OCR1A = calculate_timer_compare_time(DRIVE_COUNTERCLOCKWISE_SLOWEST_MS + DRIVE_STEP_SIZE * ((50 - percentage) / 50.0 * 100));
		}
	}
}

void set_speed(short percentage)
{
	set_speed_motor(percentage, LEFT_MOTOR);
	set_speed_motor(percentage, RIGHT_MOTOR);
}

void turn(short speed_percentage, short turn_percentage)
{
	 // Turn forward left.
	 if(turn_percentage < 50 && speed_percentage > 50)
	 {
		 set_speed_motor(90, RIGHT_MOTOR);
		 set_speed_motor(70, LEFT_MOTOR);
		 return;
	 }
	 
	 // Turn forward right.
	 if(turn_percentage > 50 && speed_percentage > 50)
	 {
		 set_speed_motor(70, RIGHT_MOTOR);
		 set_speed_motor(90, LEFT_MOTOR);
		 return;
	 }
	 
	 // Turn backward left.
	 if(turn_percentage < 50 && speed_percentage < 50)
	 {
		 set_speed_motor(10, RIGHT_MOTOR);
		 set_speed_motor(30, LEFT_MOTOR);
		 return;
	 }
	 
	 // Turn backward right.
	 if(turn_percentage > 50 && speed_percentage < 50)
	 {
		 set_speed_motor(30, RIGHT_MOTOR);
		 set_speed_motor(10, LEFT_MOTOR);
		 return;
	 }
	 
	 // Tun stationary left.
	 if(turn_percentage < 50 && speed_percentage == 50)
	 {
		 set_speed_motor(80, RIGHT_MOTOR);
		 set_speed_motor(20, LEFT_MOTOR);
	 }
	 
	 // Tun stationary right.
	 if(turn_percentage > 50 && speed_percentage == 50)
	 {
		 set_speed_motor(20, RIGHT_MOTOR);
		 set_speed_motor(80, LEFT_MOTOR);
	 }
}

void control_drive(short percentage_speed, short percentage_turn)
{	
	if(percentage_turn == 50)
	{
		set_speed(percentage_speed);	
		return;
	}
	
	turn(percentage_speed, percentage_turn);
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
