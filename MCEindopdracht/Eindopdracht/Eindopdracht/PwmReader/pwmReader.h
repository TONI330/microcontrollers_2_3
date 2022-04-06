#pragma once

void init_pwm(void);

int getTicks(void);

void pwm_reader_add_pin(int pin, int* out_ticks);