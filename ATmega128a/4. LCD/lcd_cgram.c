#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>


void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);
void FONT(char address,char font);

unsigned int i=0,j;
unsigned int arr[5][8] = {{0x0e,0x1b,0x11,0x11,0x11,0x11,0xff,0x00},
						  {0x0e,0x1b,0x11,0x11,0x11,0xff,0xff,0x00},
					      {0x0e,0x1b,0x11,0x11,0xff,0xff,0xff,0x00},
						  {0x0e,0x1b,0x11,0xff,0xff,0xff,0xff,0x00},
						  {0x0e,0x1b,0xff,0xff,0xff,0xff,0xff,0x00}};

int main(void)
{
	
	DDRC = 0xff;
	PORTC = 0x00;
	
	LCD_INIT();
	
	COMMAND(0x01);
	
	COMMAND(0x40);
	_delay_ms(2);
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
			DATA(arr[i][j]);
		}
	}
	FONT(0,0);
	_delay_ms(500);
	FONT(0,1);
	_delay_ms(500);
	FONT(0,2);
	_delay_ms(500);
	FONT(0,3);
	_delay_ms(500);
	FONT(0,4);
	_delay_ms(500);

	while (1)
	{
	}
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

void STRING(unsigned char font[], unsigned char n)
{
	int i;
	for(i=0;i<n;i++)
	DATA(font[i]);
}

void MOVE(int y, int x)
{
	unsigned char data;
	
	if(y==1)
	data = 0x80+x-1;
	else if(y==2)
	data = 0xc0+x-1;
	
	COMMAND(data);
}

void FONT(char address,char font)
{
	COMMAND(0x80|0x00+address);
	DATA(font);
	_delay_ms(500);
}