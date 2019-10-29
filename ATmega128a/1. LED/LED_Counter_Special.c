#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
    int cnt = 0; 
	
	while (1) 
    {
		if(!(PINA&0x01))
		{
			cnt++;
			_delay_ms(300);
			if(cnt  == 3)
				PORTB = 0x55;
			else if(cnt == 6)
				PORTB = 0xAA;
			else if(cnt == 9)
				PORTB = 0x0F;
			else if(cnt == 12)
				PORTB = 0xF0;
			else if(cnt == 15)
			{
				PORTB = 0x00;
				cnt = 0;
			}
		}
    }
}

