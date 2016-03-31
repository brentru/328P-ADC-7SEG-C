// Brent Rubell and David Austin
// Lab: ADC & 7 Segment Display & Interrupts

// dependencies
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

// Lookup Tables in PROGMEM
const uint8_t cathodelut[4] PROGMEM = { 0x01, 0x02, 0x08, 0x04};
const uint8_t binlut[15] PROGMEM ={
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

uint8_t currentDigit; // counts from 0=>3, tells which cathode you're supposed to drive. grab individual decimal digits of myval based off of this.

const uint8_t diglut[4];

// lcd/adc update booleans
volatile uint8_t segupdate = 0;
volatile uint8_t adcupdate = 0;
// ADC Value
volatile uint16_t adcval;

// routine to set up the ADC
void adcinit(void)
{
	ADMUX |= (1<<REFS0); // uses the AVCC voltage
	ADMUX |= (0<<MUX0);// using ADC0 & PC0
	ADCSRA |= (1<<ADEN); // ADC enabled pg 249, bottom of page
	// 50kHz < clk freq < 200kHz (pg240)
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); // prescaler w/128 division factor
	ADCSRA |= (1<<ADIE); // bit write to 1, when sreg's "i" is set, the ADC conversion complete interrupt is enabled (pg250)
}

// routine to set up the timer
void timerinit(void)
{
	TCCR0A |= (0b0010<<WGM00); //Puts the Timer into CTC mode
	TCCR0B |= (0b0101<<CS00) | (0b0000<<WGM02); //Sets prescale of Timer to divide by (5) ie. 1024
	TIMSK0 = _BV(OCIE0A); //enables the interrupt to work properly by storing a '1' in OCIE0A
	TCNT0 = 0; //starting value for the timer
	OCR0A = 65; //Max value for CTC to count to, CTC stops at OCR0A ie. 65 in this case, then triggers the interrupt
}


void printLUT(void)
{
	DDRB = cathodelut[0];
	PORTB = cathodelut[0];
	DDRD = binlut[0];
	PORTD = binlut[0];
	// segupdate = 1
}

ISR (ADC_vect)
{
	adcval = ADC; // ADC register is ADC
	/*
	//dig to be sent to 7seg
	volatile uint8_t foursig = (adcval%10);       //grabs least significant digit from adc value
	volatile uint8_t threesig = ((adcval/10)%10);  //grabs 2nd least sig digit
	volatile uint8_t twosig = ((adcval/100)%10); //grabs 3rd least sig dig
	volatile uint8_t onesig = (adcval/1000);    //grabs 1st sig digit
    diglut[4] = {onesig,twosig,threesig,foursig};
		*/
	adcupdate=1; // set update flag to 1 as adc is updated now
}

ISR (PCINT0_vect)
{
	if((PINB &(1<<PINB7)) == 1)
	{
		// low to high pin change, button pressed down
	
		// start conversion, should trigger ADC VECT
		ADCSRA |= (1<<ADSC);
		// put the value on the LCD
	}
	else
	{
		// high to low pin change, button pressed up
	}
}

ISR(TIMER0_COMPA_vect) //will be called when OCR0A is equal to TCNT0
{
	//if OCR0A matche the TCNT0
	//using /10, and mod10 break down the number into each bit to display on led
	//Sets up four variables in order to avoid changing the global variable
	PORTB = (cathodelut[currentDigit]);
	PORTD = (diglut[currentDigit]);
	currentDigit++;
	if(currentDigit == 3)
	{
		currentDigit=0;
	}
}

ISR(BADISR_vect)
{
	// handles unexpected interrupts
	// put a breakpoint here to catch unhandled interrupts
}


int main(void)
{

	// 7-seg code inits
	//int printnum = 4; // qty of #'s on 7seg
	
	
	TCCR0A |= (0b0010<<WGM00); //Puts the Timer into CTC mode
	TCCR0B |= (0b0101<<CS00) | (0b0000<<WGM02); //Sets prescale of Timer to divide by (5) ie. 1024
	TIMSK0 = _BV(OCIE0A); //enables the interrupt to work properly by storing a '1' in OCIE0A
	TCNT0 = 0; //starting value for the timer
	OCR0A = 65; //Max value for CTC to count to, CTC stops at OCR0A ie. 65 in this case, then triggers the interrupt
	
	
	ADMUX |= (1<<REFS0); // uses the AVCC voltage
	ADMUX |= (0<<MUX0);// using ADC0 & PC0
	ADCSRA |= (1<<ADEN); // ADC enabled pg 249, bottom of page
	// 50kHz < clk freq < 200kHz (pg240)
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); // prescaler w/128 division factor
	ADCSRA |= (1<<ADIE); // bit write to 1, when sreg's "i" is set, the ADC conversion complete interrupt is enabled (pg250)

	
	PORTB |= (1<<PORTB7); // turn on pullup
	PCICR |= (1<<PCIE0); // enable PCMSK0 scan
	PCMSK0 |= (1<<PCINT7); // trigger on state change

	sei(); // enable interrupts
	
	while(1)
	{
		PINC ^= _BV(1); // toggle the pinc
		
	}
}
