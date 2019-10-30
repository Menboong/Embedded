/*
 * FND_4_Shift_Hexadecimal.c
 *
 * Created: 2019-04-26 오후 1:49:08
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char fnd_pos = 0x01;
	int i=0,t=0;
	int arr[16] = {0xc0,0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8, 0x80, 0x98, 0xa0, 0x83, 0xa7, 0xa1, 0x84, 0x8E};
    DDRC = 0xFF;
	DDRG = 0xFF;
	
    while (1) 
    {
		for(i=0;i<16;i++)
		{
			_delay_ms(500);
			if(t%4==0)
				t=0;
			
			PORTG = fnd_pos << t;
			PORTC = arr[i];
			
			t++;
		}
    }
}

