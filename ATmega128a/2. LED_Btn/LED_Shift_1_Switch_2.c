/*
 * LED_Shift_1_Switch.c
 *
 * Created: 2019-04-05 오전 11:19:39
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
	PORTB = 0x01;
	
    while (1) 
    {			
		if(!(PINA&0x01))
		{
			if(PORTB == 0x80)
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
			if(PORTB == 0x01)
			{
				PORTB = 0x80;
			}
			else
			{
				PORTB = PORTB >> 1;
			}
		}
		_delay_ms(300);
    }
}

