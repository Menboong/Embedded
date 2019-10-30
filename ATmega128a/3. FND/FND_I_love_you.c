/*
 * FND_I_love_you.c
 *
 * Created: 2019-04-12 오후 1:41:59
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0x00;
	DDRC = 0xFF;

	int arr[8]= {0x30, 0x38, 0x3F, 0x3E, 0x79, 0x6E, 0x3F, 0x1C};
	int i;
	while (1) 
    {
		i=0;
		while(!(PINA &= 0x01))
		{
			if(i>7)
				i = 0;
			PORTC = arr[i];
			_delay_ms(500);
			i++;
		}
    }
}

