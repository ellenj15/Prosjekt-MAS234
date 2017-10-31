#include <avr/io.h>

void loop(void);

int main(void)
{
	DDRD = 0x01;
	
	while(1)
	{
		loop();
	}
}

void loop (void)
{
	if((PINB &= (1 << PINB1)) == 2)
	{
		PORTD &= ~(1 << PD0);
	}
	
	else
	{
		PORTD |= (1 << PD0);
	}
}