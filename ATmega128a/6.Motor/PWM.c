/*
 * PWM.c
 *
 * Created: 2019-09-25 오전 9:45:31
 * Author : 2314
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void DC_Motor(unsigned int speed)
{
	if(speed < 0)
		speed = 0;
	if(speed > 100)
		speed = 100;
	OCR1A = speed;
}


int main(void)
{
	int i;
	DDRB = 0XFF;
	
	TCCR1A = 0X82;
	TCCR1B = 0X1A;
	ICR1 = 100;
	OCR1B = 0;
	OCR1A = 0;
	
	PORTB = 0x01;
    /* Replace with your application code */
    while (1) 
    {
		for(i=50;i<100;i++)
		{
			DC_Motor(i);
			_delay_ms(100);
		}
		for(i=100;i>=50;i--)
		{
			DC_Motor(i);
			_delay_ms(100);
		}
    }
}

