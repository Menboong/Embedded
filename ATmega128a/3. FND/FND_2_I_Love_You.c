/*
 * FND_2_I_Love_You.c
 *
 * Created: 2019-04-19 오후 2:35:47
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int arr[11] = {0x4F,0xff;  ,0x47,0x40,0x41,0x06,0xff,0x11,0x40,0x63,0xff};
	int pos1=0,pos2=-1;

	DDRA = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRG = 0xFF;
	

	PORTG = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;
	
    while (1) 
    {
		if(!(PINA &= 0x01))
		{
			_delay_ms(300);
			
			PORTD = arr[pos1];
			if(pos2 != -1)
				PORTC = arr[pos2];
			pos1++;
			pos2++;
			
			if(pos1 > 10)
			{
				pos1 = 0;
			}
			if(pos2 > 10)
			{
				pos2 = 0;
			}
		}
	}
}

