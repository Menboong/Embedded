#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
	PORTB = 0x03;
	
	while (1)
	{
		if(!(PINA&0x01))
		{
			if(PORTB == 0x03 || PORTB == 0x0C || PORTB == 0x30 || PORTB == 0xC0)
				PORTB = 0x01;
			else if(PORTB == 0x80)
			{
				PORTB = 0x01;
			}
			else
			{
				PORTB = PORTB << 1;
			}
			
		}
		
		else if(!(PINA&0X02))
		{
			if(PORTB == 0x03 || PORTB == 0x0C || PORTB == 0x30 || PORTB == 0xC0)
				PORTB = 0x80;
			
			else if(PORTB == 0x01)
			{
				PORTB = 0x80;
			}
			else
			{
				PORTB = PORTB >> 1;
			}
		}
		
		else if(!(PINA&0X04))
		{
			if(PORTB == 0x01 || PORTB == 0x02 || PORTB == 0x04 || PORTB == 0x08 || PORTB == 0x10 || PORTB == 0x20 || PORTB == 0x40 || PORTB == 0x80)
				PORTB = 0x03;
			
			else if(PORTB == 0xC0)
			{
				PORTB = 0x03;
			}
			else
			{
				PORTB = PORTB << 2;
			}
		}
		
		else if(!(PINA&0X08))
		{
			if(PORTB == 0x01 || PORTB == 0x02 || PORTB == 0x04 || PORTB == 0x08 || PORTB == 0x10 || PORTB == 0x20 || PORTB == 0x40 || PORTB == 0x80)
				PORTB = 0x03;
			
			if(PORTB == 0x03)
			{
				PORTB = 0xC0;
			}
			else
			{
				PORTB = PORTB >> 2;
			}
		}
		_delay_ms(300);
	}
}