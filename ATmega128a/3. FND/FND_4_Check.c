/*
 * FND_4_Check.c
 *
 * Created: 2019-04-26 오전 10:18:32
 * Author : user
 */ 
#define  F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18};
	DDRC = 0xFF;
	DDRG = 0x0F;
    
    while (1) 
    {	PORTG = 0x02;
		PORTC = arr[0];
		_delay_ms(300);
    }
}

