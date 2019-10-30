/*
 * fndtest.c
 *
 * Created: 2019-04-26 오전 11:18:23
 * Author : user
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0xff;
	DDRG = 0XFF;
    /* Replace with your application code */
    while (1) 
    {	
		PORTG = 0X01;
		PORTC = 0x40;
    }
}

