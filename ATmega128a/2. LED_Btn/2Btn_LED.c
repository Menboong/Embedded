/*
 * button_on_off.c
 *
 * Created: 2019-03-29 오전 11:06:19
 * Author : user
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF; //led
	DDRE = 0X00; //button
	
    while (1) 
    {
	    if (((PINE&0X10)==0X00) && ((PINE&0x20)==0x00))
	    PORTB = 0x81;
		else if((PINE&0X10)==0X00)
			PORTB = 0X80;
		else if((PINE&0x20)==0x00)
			PORTB = 0x01;
		else
			PORTB = 0x00;
    }
}

