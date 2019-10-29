/*
 * 8_LED_On.c
 *
 * Created: 2019-03-22 오전 10:13:55
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
		
		//모양
		/*PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0xFB;
		_delay_ms(1000);
		PORTB = 0x30;
		_delay_ms(1000);
		*/
	}
}

