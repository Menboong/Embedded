/*
 * 8Btn_LED.c
 *
 * Created: 2019-03-29 오후 2:13:46
 * Author : user
 */ 
#define  F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0X00;
	
    while (1) 
    {
		if((PINA&0x01)==0x00)
			PORTB = 0x01;	
		if((PINA&0x02)==0x00)
			PORTB = 0x02;
		if((PINA&0x04)==0x00)
			PORTB = 0x04;
		if((PINA&0x08)==0x00)
			PORTB = 0x08;
		if((PINA&0x10)==0x00)
			PORTB = 0x10;
		if((PINA&0x20)==0x00)
			PORTB = 0x20;
		if((PINA&0x40)==0x00)
			PORTB = 0x40;
		if((PINA&0x80)==0x00)
			PORTB = 0x80;
		else
			PORTB = 0x00;
    }
}

