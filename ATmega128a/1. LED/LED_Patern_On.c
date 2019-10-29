/*
 * led_1.c
 *
 * Created: 2019-03-22 오전 11:09:09
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0x01;
		_delay_ms(500);
		PORTB = 0X02;
		_delay_ms(500);
		PORTB = 0X04;
		_delay_ms(500);
		PORTB = 0X08;
		_delay_ms(500);
		PORTB = 0X10;
		_delay_ms(500);
		PORTB = 0X20;
		_delay_ms(500);
		PORTB = 0X40;
		_delay_ms(500);
		PORTB = 0X80;
		_delay_ms(500);
		
		PORTB = 0X40;
		_delay_ms(500);
		PORTB = 0X20;
		_delay_ms(500);
		PORTB = 0X10;
		_delay_ms(500);
		PORTB = 0X08;
		_delay_ms(500);
		PORTB = 0X04;
		_delay_ms(500);
		PORTB = 0X02;
		_delay_ms(500);
    }
}

