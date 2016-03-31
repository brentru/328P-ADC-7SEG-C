// name: adc test
// title: 328p adc test
// authors: brent rubell & david Austin

// dependencies
#include <avr/interrupt.h>
#include <avr/io.h>


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


ISR (ADC_vect)
{
	adcval = ADC; // ADC value variable is the value of ADC
  ADCSRA |= (1<<ADSC); // adc conversion

}



ISR(BADISR_vect)
{
	// handles unexpected interrupts
	// put a breakpoint here to catch unhandled interrupts
}


// main routine
int main (void)
{
  adcinit();
  sei();
  ADCSRA |= (1<<ADSC); // adc conversion
  while (1)
  {
    // do nothing
  }
}
