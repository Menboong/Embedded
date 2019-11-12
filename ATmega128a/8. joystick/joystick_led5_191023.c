/*
 * joy_stick_lcd.c
 *
 * Created: 2019-10-23 오전 10:08:26
 * Author : 2314
 */ 
#define  F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void ADC_Init(void);
int ADC_Read(char channel);
void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_PRINT(unsigned char* arr,int size,char addr);

int main(void)
{
	char adc_x_buff[20];
	char adc_y_buff[20];
	char x[2] = "x=";
	char y[2] = "y=";
	char on[2] = "on";
	char off[3] = "off";
	int adc_value = 0;
	
	ADC_Init();
	LCD_INIT();
	COMMAND(0X01);

	DDRA = 0xff;
	
    while (1) 
    {	
		LCD_PRINT(x,2,0x00);
		LCD_PRINT(y,2,0x40);
		
		/*x축*/
		adc_value = ADC_Read(1);
		sprintf(adc_x_buff,"%d",adc_value);
		_delay_ms(10);
		
		if(adc_value<400)
			PORTA = 0x01;
		else if(adc_value > 600)
			PORTA = 0x02;
		else
			PORTA = 0x00;
			
		if(adc_value<10)
			LCD_PRINT(adc_x_buff,1,0x05);
		else if(adc_value<100)
			LCD_PRINT(adc_x_buff,2,0x04);
		else if(adc_value<1000)
			LCD_PRINT(adc_x_buff,3,0x03);
		else
			LCD_PRINT(adc_x_buff,4,0x02);
		
		/*y축*/
		adc_value = ADC_Read(0);
		sprintf(adc_y_buff,"%d",adc_value);
		_delay_ms(10);
		
		if(adc_value<500)
			PORTA = 0x04;
		else if(adc_value>600)
			PORTA = 0x08;
		else
			PORTA = 0x00;
		
		if(adc_value<10)
			LCD_PRINT(adc_y_buff,1,0x45);
		else if(adc_value<100)
			LCD_PRINT(adc_y_buff,2,0x44);
		else if(adc_value<1000)
			LCD_PRINT(adc_y_buff,3,0x43);
		else
			LCD_PRINT(adc_y_buff,4,0x42);
		
		adc_value = ADC_Read(2);
		_delay_ms(10);
		
		if(adc_value <= 0)
		{
			LCD_PRINT(on,2,0x07);
			PORTA = 0x10;
		}
		else
		{
			LCD_PRINT(off,3,0x47);
			PORTA = 0x00;
		}
		_delay_ms(10);
		COMMAND(0x01);
    }
}

void ADC_Init()
{
	DDRF = 0X00;
	ADCSRA = 0X87;
	ADMUX = 0X40;
}
int ADC_Read(char channel)
{
//	int adc_value;
	ADMUX = 0X40 | (channel & 0x07);
	_delay_us(50);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & 0x10) != 0x10);
	ADCSRA |= (1 << ADIF);
	return ADCW;
}

void COMMAND(unsigned char byte) // 명령어 함수
{
	_delay_ms(2);
	PORTC = byte&0xf0;	//명령어쓰기
	PORTC &= 0b11111100;	//RS=0, RW=0, 명령어를 쓰도록 설정
	_delay_us(1);			//RS & RW setup time
	PORTC |= 0b00000100;	//E = 1, lcd동작
	_delay_us(1);			//E pulse width time
	PORTC &= 0b11111011;	//E=0
	
	PORTC = (byte<<4)&0xf0; //명령어쓰기
	PORTC &= 0b11111100;	//RS =0, RW =0 명령어를 쓰도록 설정
	_delay_us(1);
	PORTC |= 0b00000100;	//E=1 lcd동작
	_delay_us(1);
	PORTC &= 0b11111011;	//E=0
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	PORTC = byte&0xf0;		//상위 4비트 쓰기
	PORTC |= 0b00000001;
	PORTC &= 0b11111101;	//RS,RW설정
	_delay_us(1);
	PORTC |= 0b00000100;	//E=1, lcd동작
	_delay_us(1);
	PORTC &= 0b11111011;	//E=0
	
	PORTC = (byte<<4)&0xf0;	//하위 4비트 쓰기
	PORTC |= 0b00000001;
	PORTC &= 0b11111101;	//RS,RW설정
	_delay_us(1);
	PORTC |= 0b00000100;	//E=1, lcd동작
	_delay_us(1);
	PORTC &= 0b11111011;	//E=0
}
void LCD_INIT(void)
{
	DDRC = 0Xff;
	_delay_ms(30);
	
	/*function set*/
	COMMAND(0b00101000);
	_delay_us(39);
	
	/*display on/off control*/
	COMMAND(0b00001100);
	_delay_us(39);
	
	/*clear display*/
	COMMAND(0b00000001);
	//COMMAND(0b00000010);
	_delay_ms(1.63);
	
	/*entry mode set*/
	COMMAND(0b00000110);
}
void LCD_PRINT(unsigned char* arr,int size,char addr)
{
	int i;
	
	COMMAND(0x80|addr);
	for(i=0;i<size;i++)
	{
		if(((addr | 0x80) + i) == 0x90){
			COMMAND(0x80 | 0x40);
		}
		if(((addr|0x80)+i) == 0xd0){
			COMMAND(0x80);
		}
		DATA(arr[i]);
	}
}
