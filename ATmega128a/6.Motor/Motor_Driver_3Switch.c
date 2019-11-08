/*
 * Motor_Driver_3Switch.c
 *
 * Created: 2019-09-18 오전 10:20:22
 * Author : 2314
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0XFF;
	DDRD = 0XFF;
	DDRE = 0X00;	
    /* Replace with your application code */
    PORTD = 0X00;
	
	while (1) 
    {
		if(!(PINE&0x01))
		{
			PORTB = 0x70;
			PORTD = 0X0F;
		}
		else if(!(PINE&0X02))
		{
			PORTD = 0X00;
			PORTB = 0X00;
		}
		else if(!(PINE&0X04))
		{
			PORTB = 0XB0;
			PORTD = 0XF0;
		}
		
    }
}

