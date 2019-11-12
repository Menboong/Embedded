/*
 * cds.c
 *
 * Created: 2019-10-16 오전 9:55:34
 * Author : milkyway
 */ 
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define cds_10	340
#define cds_100	730

int init_adc() {
	ADMUX = 0x40;
	ADCSRA = 0x87;
}

int read_adc() {
	unsigned char adc_low, adc_high;
	unsigned int value;
	
	ADCSRA |= 0x40;
	
	while((ADCSRA & 0x10) != 0x10);
	
	adc_low = ADCL;
	adc_high = ADCH;
	value = (adc_high << 5) | adc_low;
	
	return value;
}

void display_LED(unsigned int value) {
	if (value < 5) PORTA = 0x01;
	else if (value < 10) PORTA = 0x03;
	else if (value < 20) PORTA = 0x07;
	else if (value < 30) PORTA = 0x0f;
	else if (value < 40) PORTA = 0x1f;
	else if (value < 50) PORTA = 0x3f;
	else if (value < 60) PORTA = 0x7f;
	else if (value < 70) PORTA = 0xff;
}

int main(void)
{
	unsigned int value;
	DDRA = 0xff;
	DDRF = 0x00;
	init_adc();
    while (1) 
    {
		value = read_adc();
		display_LED(value);
    }
}