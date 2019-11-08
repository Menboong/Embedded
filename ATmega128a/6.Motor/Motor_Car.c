#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

#define RF 0XF1
#define RB 0XF2
#define LF 0XF4
#define LB 0XF8
#define STOP 0X00

int main(void)
{
	DDRB = 0XFF;
	DDRD = 0XFF;
	DDRE = 0X00;
	
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE&0X01))
		{
			PORTB = STOP;
			PORTD = 0X01 | 0X04 | 0X10;
		}
		else if(!(PINE&0x02))
		{
			PORTB = LF | RF;
			PORTD = 0X02;
		}
		
		else if(!(PINE&0x04))
		{
			PORTB = LF;
			PORTD = 0X01 | 0X04;
		}
		
		else if(!(PINE&0x08))
		{
			PORTB = LB | RB;
			PORTD = 0X08;
		}
		else if(!(PINE&0x10))
		{
			PORTB = RF;
			PORTD = 0X11;
		}
		
    }
}

