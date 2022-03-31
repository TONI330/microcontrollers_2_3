#include <asf.h>

{
	int main (void)
	{
		
		// Set ADC prescaler to 64
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
		
	}

	
}
