// Brent Rubell and David Austin
// Lab: ADC + 7 Segment Display + Interrupts

// libs
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	// 7-seg code inits
	int printnum = 4; // qty of #'s on 7seg
	const uint_8 cathodelut[4] PROGMEM = { 0x01, 0x02, 0x08, 0x04};
	const uint_8 binlut[10] PROGMEM ={
		0b00111111, /* 0 */
		0b00000110, /* 1 */
		0b01010011, /* 2 */
		0b01001111, /* 3 */
		0b01100110, /* 4 */
		0b01101101, /* 5 */
		0b01111101, /* 6 */
		0b00000111, /* 7 */
		0b01111111, /* 8 */
		0b01100111, /* 9 */
		0b01110111, /* 10 */
		0b01111110, /* A */
		0b00111001, /* B */
		0b01011110, /* C */
		0b01111001, /* D */
		0b01110001  /* E */

	};


	// interrupt setup
	ADCSRA |= (1<<ADEN); // ADC enabled pg 249, bottom of page
	// 50kHz < clk freq < 200kHz (pg240)
	ADCSRA |= (7<<ADPS0;) // prescaler w/128 division factor
	ADMUX |= (0b01<<REFS0); // uses the AVCC voltage 
	ADCSRA |= (1<<ADIE) // bit write to 1, when sreg's "i" is set, the ADC conversion complete interrupt is enabled (pg250)


	// portb setup
	DDRB0 &= ~(1<<DDB0); // clear the PB0
	// PB0 is now an input 
	PORTB |= (1<<PORTB0); // turn on pullup
	//pb0 is now an input w/pull-up enabled
	PCICR |= (1<<PCIE0); // enable PCMSK0 scan
	PCMSK0 |= (1<<PCINT0); // trigger on state change

	sei(); // enable interrupts


	while(1)
	{
		PINC = STUFF NEEDS TO GO HERE
		// do nothing b/c interrupt is handling this instead
	}	
}

uint16_t GetADC(uint8_t ADCh)
{
	// masking & channel select (ADCh is channel)
	ADMUX = (ADMUX & 0b00001111) | (ADCh & 0b00001111); 
	ADCSRA |= (1<<ADSC); 

	// wait for adc conversion to finish
	while((ADCSRA & _BV(ADSC)));
	// return ADC result
	return ADC;
}

int printLUT(void)
{
	DDRB = cathodelut[0];
	PORTB = cathodelut[0];
	DDRD = binlut[0];
	PORTD = binlut[0];
}

ISR (ADC_VECT)
{
	// do stuff with adc here
}
ISR (PCINT0_VECT)
{
	// 
	if((PINB &(1<<PINB0)) == 1)
	{
		// low to high pin change
	}
	else
	{
		// high to low pin change
	}
}


ISR(BADISR_vect)
{
	// handles unexpected interrupts
	// put a breakpoint here to catch unhandled interrupts
}
