/*
 * btn_toggle.c
 *
 * Created: 2019-04-05 오전 9:51:55
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x0C;
	PORTB = 0x04;
	
    while (1) 
    {
		if(!(PINB & 0X01))
		{
			PORTB ^= (PINB=0x04)^(PINB=0x08);
			_delay_ms(300);
		}
			
    }
}

