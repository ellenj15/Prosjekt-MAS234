/*
 * UferdigSoftBlink.cpp
 *
 * Created: 31.10.2017 11:29:35
 * Author : ellen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

bool rising = true;
float desiredIntensity = 0;

int main(void)
{
	DDRB |= (1 << PB2);
	
	cli();
	TCCR1A |= (1 << WGM11) | (1 << WGM10) | (1 << COM1B1);
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK1 |= (1 << TOIE1);
	OCR1B = 0;
	sei();
	
	while(1){}
}

ISR(TIMER1_OVF_vect)
{
	if(rising == true && desiredIntensity < 244)
	{
		desiredIntensity = desiredIntensity + 1;
	}
	
	else if(desiredIntensity >= 244 || (desiredIntensity > 0 && rising == false))
	{
		desiredIntensity = desiredIntensity - 1;
		rising = false;
	}
	
	else
	{
		rising = true;
		desiredIntensity = desiredIntensity + 1;
	}
	
	OCR1B = desiredIntensity * desiredIntensity * 0.01718;
}