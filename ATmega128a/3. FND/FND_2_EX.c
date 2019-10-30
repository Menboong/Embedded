/*
 * FND_2_EX.c
 *
 * Created: 2019-04-19 오전 10:46:43
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRG = 0xFF;
	
	PORTC = 0xFF;
	PORTD = 0xFF;
	PORTG = 0XFF;
    while (1) 
    {
		PORTC = 0x00;
		PORTD = 0x00;
		_delay_ms(500);
		PORTC = 0xFF;
		PORTD = 0xFF;
		_delay_ms(500);
		
    }
}

