/*
 * Program.cpp
 *
 * Created: 31.10.2017 11:28:20
 * Author : ellen
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

uint16_t blinkTimeMs = 1000;
uint16_t blinkTimeCounter;

uint8_t counterValue = 0;
uint8_t counterTarget;

bool ledOn = false;
bool ledBrightening = true;

double dutyCycle;

int main(void)
{
	cli();								// Slå av interrupts.
	
	DDRD	=	0xFF;					// Setter port D til output.
	PORTD	=	0x00;					// Setter utgangene på port D lave.
	
	TCCR1A	=	0;						//
	TCCR1B	=	0;						// Nullstiller timer 1.
	TCNT1	=	0;						//

	OCR1A	=	199;					// Hvor langt han teller før interrupt ( 16*10^6 Hz/ ( 8 (prescaler) * 10 000 Hz ) ) - 1

	TCCR1B |=	(1 << WGM12);			// "Clear on Timer Compare match" - Setter timer 1 til 0 etter at den har interruptet.
	TCCR1B |=	(1 << CS11);			// Setter prescaler til 8.
	TIMSK1 |=	(1 << OCIE1A);			// Gjør at timeren interrupter ved compare match.
	
	sei();								// Slå på interrupts.
	
	while(1){}
}

ISR(TIMER1_COMPA_vect)
{
	// Styrer verdien for duty cycle på LED.
	
	blinkTimeCounter = blinkTimeCounter + 1;
	
	if(blinkTimeCounter >= blinkTimeMs / 20)
	{
		blinkTimeCounter = 0;
		
		if(dutyCycle < 100 && ledBrightening == true)
		{
			dutyCycle = dutyCycle + 1;
		}
		
		else if(dutyCycle > 0)
		{
			ledBrightening = false;
			dutyCycle = dutyCycle - 1;
		}
		
		else
		{
			ledBrightening = true;
		}