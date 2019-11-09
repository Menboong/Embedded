/*
 * ServoMotor.c
 *
 * Created: 2019-10-02 오전 8:45:16
 * Author : 2314
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

unsigned int distance;

void Timer_Init()
{
		TCCR1A = (1<<COM1A1) | (1<<WGM11);
		TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
		ICR1 = 4999;	
		OCR1A =	375;	//  0도) 20:1.5 = 4999:x = 375   90도) 20:2 = 4999:x = 500  -90도) 20:1 = 4999:x = 250
		TCNT1 = 0X00;
}

void Distance()
{
	TCCR3B = 0X03;
	PORTE &= ~(1<<TRIG);
	_delay_us(10);
	PORTE |= (1<<TRIG);
	_delay_us(10);
	PORTE &= ~(1<<TRIG);
	while(!(PINE&(1<<ECHO)));
	TCNT3 = 0x0000;
	while(PINE&(1<<ECHO));
	TCCR3B = 0x00;
	distance = SOUND_VELOCITY * (TCNT3 * 4/2)/1000;
}

int main(void)
{
	DDRA = 0xff;
	DDRB = 0X20;
	DDRE = ((DDRE|(1<<TRIG))&~(1<<ECHO));
	PORTB = 0X00;
	
	Timer_Init();
    
	while (1) 
    {
		Distance();
		//PORTA = 0xff;
		
		if(distance<100)
			OCR1A = 500;
		else if(distance<200)
			OCR1A = 438;
		else if(distance<300)
			OCR1A = 375;
		else if(distance<400)
			OCR1A = 313;
		else if(distance<500)
			OCR1A = 250;
		
		_delay_ms(100);
		
    }
}

