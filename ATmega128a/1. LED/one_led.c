/*
 * one_led.c
 *
 * Created: 2019-03-21 오전 10:17:36
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0X01;
		_delay_ms(1000);
		PORTB = 0x00;
		_delay_ms(1000);
    }
}

