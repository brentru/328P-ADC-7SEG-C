// Brent Rubell and David Austin
// Lab: ADC + 7 Segment Display + Interrupts

// libs
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	/* 
	328P ADC Pinout
	PC5 = ADC5
	PC4 = ADC4
	PC3 = ADC3
	PC2 = ADC2
	PC1 = ADC1
	PC0 = ADC0
	*/

	// i/o setup
	DDRB=0; // pinB here, it's on Pin B7
	// enable the pullup, PINIO in manual, 14.2 

	//set up the LED
	



	


	while (1)
	{
		PINC = 
		// do nothing b/c interrupt is handling this instead
	}
	return 0;
}


ISR(PCINT0_VECT)
{
	// if to detect change
		ADSRA |= (1<<ADSC); // start conversion 
		// toggle pin c

}

// isr for 7-segment display code 
ISR(ADC_SEG){
	// space for changing the 7seg display to reflect
	// the values grabbed by the interrupt 

	unsigned char adcValue[4];
	//put the adcvalue into the LCD

}

ISR(BADISR_vect)
{
	// handles unexpected interrupts
}
