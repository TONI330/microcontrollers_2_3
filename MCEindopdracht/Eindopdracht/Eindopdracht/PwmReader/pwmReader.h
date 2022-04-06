#pragma once

/*
	This method starts the timers to read pwm signals from the added channels (PB0 to PB3).
*/
void init_pwm(void);

/*
	This method is used to add a @param pin to the list of pins that read a pwm signal.
	@param out_ticks is used to track the returned duty cycle in ticks.
*/
void pwm_reader_add_pin(int pin, int* out_ticks);
