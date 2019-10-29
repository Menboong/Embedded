/*
 * LED_Patern_Special.c
 *
 * Created: 2019-03-22 오후 1:41:39
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
    int i;
	unsigned char left;
	unsigned char right;
    while (1) 
    {
		PORTB = 0x00;

		for (i=0; i<4; i++) 
		{
			left = 0b10000000 >> i;
			right = 0b00000001 << i;
			PORTB = PORTB ^ (left | right);
			_delay_ms(1000);
		}
		
		for (i=0; i<4; i++) 
		{
			left = 0b00010000 << i;
			right = 0b00001000 >> i;
			PORTB = PORTB ^ (left | right);
			_delay_ms(1000);
		}
		
		for(i=0;i<4;i++)
		{
			left = 0b01111111 >> i;  //01110000     00111111    00011111
			right = 0b11111110 << i;// 00001110     11111100    11111000
			PORTB = left & right;  
			_delay_ms(1000);  
		}
		
		for (i=0;i<4;i++)
		{
			left = 0b00010000 << i;
			right = 0b00001000 >> i;
			PORTB = PORTB ^ (left | right);
			_delay_ms(1000);
		}
    }
}

