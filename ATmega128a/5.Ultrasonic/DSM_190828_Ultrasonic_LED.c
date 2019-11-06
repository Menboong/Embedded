/*
 * DSM_190828_Ultrasonic_Buzzer.c
 *
 * Created: 2019-08-28 오전 10:00:41
 * Author : 2314
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

int main(void)
{
	unsigned int distance;
	unsigned int i;
	
	DDRD = 0xff;
	DDRE = ((DDRE|(1<<TRIG))&~(1<<ECHO));
	
	while (1) 
    {
		TCCR1B = 0X03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE&(1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE&(1<<ECHO));
		TCCR1B = 0x00;
		distance = SOUND_VELOCITY * (TCNT1 * 4/2)/1000;
		
		
		if(distance<100)
			PORTD = 0xff;		
		else if(distance<200)
			PORTD = 0x7f;
		else if(distance<300)
			PORTD = 0x3f;
		else if(distance<400)
			PORTD = 0x1f;
		else if(distance<500)
			PORTD = 0x0f;
		else if(distance<600)
			PORTD = 0x07;
		else if(distance<700)
			PORTD = 0x03;
		else if(distance<800)
			PORTD = 0x01;
		else if(distance<900)
			PORTD = 0x00;
    }
}

