/*
 * LED_Blink.c
 *
 * Created: 2019-03-22 오전 11:26:29
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;   
	while (1) 
    {	
		PORTB = 0xFF;
		_delay_ms(12);
		PORTB = 0X00;
		_delay_ms(12);
    }
}

