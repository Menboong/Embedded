/*
 * ServoMotor.c
 *
 * Created: 2019-10-02 오전 8:45:16
 * Author : 2314
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned int distance;

void Timer_Init()
{
		TCCR1A = (1<<COM1A1) | (1<<WGM11);
		TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
		ICR1 = 4999;	
		OCR1A =	375;	//  0도) 20:1.5 = 4999:x = 375   90도) 20:2 = 4999:x = 500  -90도) 20:1 = 4999:x = 250
		TCNT1 = 0X00;
}

int main(void)
{
	DDRB = 0X20;
	PORTB = 0X00;
	Timer_Init();
    while (1) 
    {
		OCR1A = 500;
		_delay_ms(500);
		OCR1A = 438;
		_delay_ms(500);
		OCR1A = 375;
		_delay_ms(500);
		OCR1A = 313;
		_delay_ms(500);
		OCR1A = 250;
		_delay_ms(500);
    }
}

