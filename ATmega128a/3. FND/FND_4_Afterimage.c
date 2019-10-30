/*
 * FND_4_Afterimage.c
 *
 * Created: 2019-04-26 오전 11:27:53
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18, 0x20, 0x03, 0x27, 0x21, 0x04, 0x0E};
	DDRG = 0XFF;
	DDRC = 0XFF;

    /* Replace with your application code */
    while (1) 
    {
		PORTG = 0X01;
		PORTC = arr[1];
		_delay_ms(3);
		PORTG = 0X02;
		PORTC = arr[2];
		_delay_ms(3);
		PORTG = 0X04;
		PORTC = arr[3];
		_delay_ms(3);
		PORTG = 0X08;
		PORTC = arr[4];
		_delay_ms(3);
		
    }
}

