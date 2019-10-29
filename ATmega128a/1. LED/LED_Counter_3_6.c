/*
 * LED_Counter_3_6.c
 *
 * Created: 2019-04-05 오후 2:56:43
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	
    int cnt = 0; 
	
	while (1) 
    {
		if(!(PINA&0x01))
		{
			cnt++;
			_delay_ms(300);
			if(cnt == 3)
				PORTB = 0xFF;
			else if(cnt == 6)
				PORTB = 0x00;
		}
	
    }
}

