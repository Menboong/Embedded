/*
 * LED_8_Toggle_Switch_1.c
 *
 * Created: 2019-04-05 오전 10:46:13
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0x00;
	
	PORTB = 0xFF;
	
    while (1) 
    {
		if(!(PINA&0x01))
		{
			PORTB ^= 0xFF;
			_delay_ms(300);
		}
    }
}

