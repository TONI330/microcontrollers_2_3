#define F_CPU 16e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "drive/drive.h"

int main(void)
{
	sei(); // Enable interrupts.
	
	init_servos();

    while (1) 
    {
    }
}
