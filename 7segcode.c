/*
 * _7segmentc.c
 * 7 segment code (powertest) ported to C from ASM
 * Created: 3/26/2016 8:38:26 PM
 *  Author: brent
 */ 


#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	
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
	
	
    while(1)
    {
	 
	 if(printnum == 1)
	 {
		 /* Display only 1 number */
		 DDRB = cathodelut[0];
		 PORTB = cathodelut[0];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
	 }
	 else if (printnum == 2)
	 {
		 /* Display two numbers */
		 DDRB = cathodelut[0];
		 PORTB = cathodelut[0];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[1];
		 PORTB = cathodelut[1];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
	 }
	 else if (printnum == 3)
	 {
		 /* Display two numbers */
		 DDRB = cathodelut[1];
		 PORTB = cathodelut[1];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[1];
		 PORTB = cathodelut[1];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[3];
		 PORTB = cathodelut[3];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
	 }
	 else if (printnum == 4)
	 {
		 /* Display two numbers */
		 DDRB = cathodelut[0];
		 PORTB = cathodelut[0];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[1];
		 PORTB = cathodelut[1];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[2];
		 PORTB = cathodelut[2];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
		 DDRB = cathodelut[3];
		 PORTB = cathodelut[3];
		 DDRD = binlut[0];
		 PORTD = binlut[0];
		 _delay_ms(4);
	 }
	
	else
	{
		// nothing
	}
}
	
	
  
}

