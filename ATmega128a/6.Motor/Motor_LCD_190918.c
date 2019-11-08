/*
 * Motor_LCD_190918.c
 *
 * Created: 2019-09-18 오전 11:22:17
 * Author : 2314
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void LCD_INIT(void);
void DATA(unsigned char byte);
void COMMAND(unsigned char byte);
void STRING(unsigned char font[], unsigned char n);

int main(void)
{
	char STOP[5] = "STOP";
	char LEFT[5] = "LEFT";
	char RIGHT[6] = "RIGHT";
	
	DDRB = 0xff;
	DDRC = 0XFF;
	DDRD = 0XFF;
	DDRE = 0X00;
	
	PORTB = 0X00;
	PORTC = 0X00;
	
	LCD_INIT();
    /* Replace with your application code */
    while (1) 
    {
		if(!(PINE&0x01))
		{
			PORTB = 0x70;
			PORTD = 0X0F;
			COMMAND(0X01);
			STRING(LEFT,4);
		}
		else if(!(PINE&0X02))
		{
			PORTB = 0X00;
			PORTD = 0X00;
			COMMAND(0X01);
			STRING(STOP,4);
		}
		else if(!(PINE&0X04))
		{
			PORTB = 0XB0;
			PORTD = 0XF0;
			COMMAND(0X01);
			STRING(RIGHT,5);
		}
    }
}

void COMMAND(unsigned char byte) // 명령어 함수
{
	_delay_ms(2);
	PORTC = byte&0xf0;	//명령어쓰기
	PORTC &= 0b11111100;	//RS=0, RW=0, 명령어를 쓰도록 설정
	_delay_us(39);			//RS & RW setup time
	PORTC |= 0b00000100;	//E = 1, lcd동작
	_delay_us(39);			//E pulse width time
	PORTC &= 0b11111011;	//E=0
	
	PORTC = (byte<<4)&0xf0; //명령어쓰기
	PORTC &= 0b11111100;	//RS =0, RW =0 명령어를 쓰도록 설정
	_delay_us(39);
	PORTC |= 0b00000100;	//E=1 lcd동작
	_delay_us(39);
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
	_delay_ms(30);
	
	/*function set*/
	COMMAND(0b00101000);
	_delay_us(39);
	
	/*display on/off control*/
	COMMAND(0b00001100);
	_delay_us(39);
	
	/*clear display*/
	COMMAND(0b00000001);
	COMMAND(0b00000010);
	_delay_ms(1.63);
	
	/*entry mode set*/
	COMMAND(0b00000110);
}

void STRING(unsigned char font[], unsigned char n)
{
	int i;
	for(i=0;i<n;i++)
		DATA(font[i]);
}
