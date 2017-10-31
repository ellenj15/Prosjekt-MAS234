/*
 * Dimmer.cpp
 *
 * Created: 31.10.2017 11:19:04
 * Author : ellen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

uint8_t counterValue = 0;
uint8_t counterTarget = 0;

bool ledOn = false;
float analogRead;

int main(void)
{
	cli();								// Slå av interrupts.
	
	DDRD	=	0x01;					// Setter port D til output.

	OCR1A	=	199;					// Hvor langt han teller før interrupt ( 16*10^6 Hz/ ( 8 (prescaler) * 10 000 Hz ) ) - 1

	TCCR1B |=	(1 << WGM12);			// "Clear on Timer Compare match" - Setter timer 1 til 0 etter at den har interruptet.
	TCCR1B |=	(1 << CS11);			// Setter prescaler til 8.
	TIMSK1 |=	(1 << OCIE1A);			// Gjør at timeren interrupter ved compare match.
	
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
	ADMUX |= (1 << REFS0);
	
	sei();								// Slå på interrupts.
	
	while(1){}
}

ISR(TIMER1_COMPA_vect)
{
	if(counterValue < counterTarget && ledOn == false)
	{
		PORTD |= (1 << PD0);
		ledOn = true;
	}
	
	else if(counterValue >= counterTarget && ledOn == true)
	{
		PORTD &= ~(1 << PD0);
		ledOn = false;
	}
}
	
