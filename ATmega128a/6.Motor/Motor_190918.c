/*
 * Motor_190918.c
 *
 * Created: 2019-09-18 오전 8:52:26
 * Author : 2314
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xff;
	DDRB = 0xff;
	while (1) 
    {
		
		PORTB = 0XFF;   
		PORTD = 0xC0;
		_delay_ms(5000);
		
		PORTB = 0X00;
		PORTD = 0x00;
		_delay_ms(5000);
		
		PORTB = 0XFF;
		PORTD = 0x30;
		_delay_ms(5000);
		
		PORTB = 0X00;
		PORTD = 0x00;
		_delay_ms(5000);
		
    }
}

