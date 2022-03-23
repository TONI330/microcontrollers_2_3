#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/interrupt.h>

// initialize timer, interrupt and variable
void timer1_init() {
	//set up timer in PWM, Phase and frequency Correct mode
	//TCCR1A |= (1 << WGM10);
	TCCR1A = 0b01010110;
	// set up timer with prescaler = 8 and PWM, Phase and frequency correct mode
	TCCR1B |= (1 << WGM13) | (1 << CS11);
	// initialize counter
	TCNT1 = 0;
	ICR1 = 20000;
	// initialize compare value
	OCR1A = 20000 - 1350;
	// enable compare interrupt
	//TIMSK1 |= (1 << OCIE1A)|(1<<TOIE1); // This is wrong!!!!
	TIMSK1 |= (1 << OCIE1A); // This works
	
}
// this ISR is fired whenever a match occurs
// hence, toggle led here itself..
ISR( TIMER1_COMPA_vect) {
	// toggle led here
	PORTB ^= (1 << 7);
}
int main(void) {
	// connect led to pin PB7
	DDRB = 0xFF;
	// initialize timer
	timer1_init();
	// enable global interrupts
	sei();
	// loop forever
	while (1) {
		// do nothing
		// whenever a match occurs, ISR is fired
		// toggle the led in the ISR itself
		// no need to keep track of any flag bits here
		// done!
	}
}

