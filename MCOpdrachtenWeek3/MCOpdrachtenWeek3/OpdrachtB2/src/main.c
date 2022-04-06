#include <asf.h>
#include <interrupt.h>

#define FIFTEENMILISECONDS 117
#define TWENTYFIVEMILISECONDS 195

int main (void)
{	
		// Enable interrupts
		sei();
	
		// Set up timer in PWM, Phase and frequency Correct mode.
		TCCR1A = 0b01010110;
	
		// Set up timer with prescaler 1024
		TCCR1B |= (1 << CS22) | (1 << CS20);
		
		// Reset timer 2
		TCNT1 = 0;
		
		// Set overflow over at least 40ms, now on 51.2ms
		ICR1 = 400;
		
		// Interrupt on 15ms
		OCR1A = FIFTEENMILISECONDS;
		
		// Enable compare interrupts
		TIMSK |= (1 << OCIE1A);

		// Set PORTD.7 to output
		DDRD |= (1 << 7);
		
		for(;;);
}

ISR(TIMER1_COMPA_vect) 
{
	if(OCR1A == FIFTEENMILISECONDS) {
		// Set timer interrupt on 25ms
		OCR1A = TWENTYFIVEMILISECONDS;
		
		// Set PORTD.7 to high
		PORTD |= (1 << 7);
		
	} else {
		// Set timer interrupt on 15ms
		OCR1A = FIFTEENMILISECONDS;
		
		// Set PORTD.7 to low
		PORTD ^= (1 << 7);
	}
	TCNT2 = 0;
}

