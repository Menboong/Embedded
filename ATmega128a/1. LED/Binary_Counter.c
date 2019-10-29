/*
 * Binary_Counter_2314.c
 *
 * Created: 2019-03-29 오전 9:54:19
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB = 0XFF;
	PORTB = 0X00;
	
    while (1) 
    {
		_delay_ms(1000);
		PORTB += 1; 
    }
}

