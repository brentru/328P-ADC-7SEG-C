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
	



	
	// interrupt setup
	ADCSRA |= (1<<ADEN); // ADC enabled pg 249, bottom of page
	// 50kHz < clk freq < 200kHz (pg240)
	ADCSRA |= (7<<ADPS0;) // prescaler w/128 division factor


	ADMUX |= (0b01<<REFS0); // uses the AVCC voltage 

	ADCSRA |= (1<<ADIE) // bit write to 1, when sreg's "i" is set, the ADC conversion complete interrupt is enabled (pg250)

	sei(); // enable interrupts


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
