#define F_CPU 16000000UL
 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0XFF;
	DDRD = 0X00;
	PORTD = 0XFF;
	
    while (1) 
    {
		if(!(PIND&0X01))
			PORTA = 0X01;
		else
			PORTA = 0x00;
    }
}

