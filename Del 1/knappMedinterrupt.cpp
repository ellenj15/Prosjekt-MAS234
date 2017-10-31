/*
 * KnappMedInterrupt.cpp
 *
 * Created: 31.10.2017 11:25:03
 * Author : ellen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

int debouncePreventionDelay = 100; // Value from 0 to 255 (Delay[ms] = Value * 0.064)

bool overflow = true;
bool buttonPushed = false;

int main(void)
{
	DDRD = (1 << PD0);
	
	SREG &= ~(1 << 7);
	PCICR |= (1 << PCIE0);
	PCMSK0 |= (1 << PCINT1);
	
	TCCR0B |= (1 << CS02) | (1 << CS00); // 1024 prescaler
	TIMSK0 |= (1 << TOIE0);
	SREG |= (1 << 7);
	
	while(1){}
}

ISR(PCINT0_vect)
{
	if(debouncePreventionDelay < TCNT0 || overflow == true)
	{
		TCNT0 = 0;
		overflow = false;
		
		if(buttonPushed == false)
		{
			PORTD ^= (1 << PD0);
			buttonPushed = true;
		}
		
		else
		{
			buttonPushed = false;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	overflow = true;
}



