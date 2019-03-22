/*
 * LED_2.c
 *
 * Created: 2019-03-22 오전 11:12:02
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
		PORTB = 0XFE;
		_delay_ms(500);
		PORTB = 0xFD;
		_delay_ms(500);
		PORTB = 0XFB;
		_delay_ms(500);
		PORTB = 0XF7;
		_delay_ms(500);
		PORTB = 0XEF;
		_delay_ms(500);
		PORTB = 0XDF;
		_delay_ms(500);
		PORTB = 0XBF;
		_delay_ms(500);
		PORTB = 0X7F;
		_delay_ms(500);
		
		PORTB = 0XBF;
		_delay_ms(500);
		PORTB = 0XDF;
		_delay_ms(500);
		PORTB = 0XEF;
		_delay_ms(500);
		PORTB = 0XF7;
		_delay_ms(500);
		PORTB = 0XFB;
		_delay_ms(500);
		PORTB = 0xFD;
		_delay_ms(500);
		}
}

