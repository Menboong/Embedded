/*
 * FND_4_From_0_To_F.c
 *
 * Created: 2019-04-26 오전 11:22:13
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18, 0x20, 0x03, 0x27, 0x21, 0x04, 0x0E};
	int i;
	
	DDRG = 0xff;
	DDRC = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0x01;
		for(i=0;i<16;i++)
		{
			PORTC = arr[i];
			_delay_ms(300);
		}
    }
}

