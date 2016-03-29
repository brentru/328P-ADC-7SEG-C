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

	//


	DDRB0 &= ~(1<<DDB0); // clear the PB0
	// PB0 is now an input 

	PORTB |= (1<<PORTB0); // turn on pullup
	//pb0 is now an input w/pull-up enabled

	PCICR |= (1<<PCIE0); // enable PCMSK0 scan
	PCMSK0 |= (1<<PCINT0); // trigger on state change

	sei(); enable interrupts

	while(1)
	{
		// main program
	}	
}
int printLUT(void)
{
	DDRB = cathodelut[0];
	PORTB = cathodelut[0];
	DDRD = binlut[0];
	PORTD = binlut[0];
}


ISR (PCINT0_VECT)
{
	//
}