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
void FONT(char address,char font,int pos);
void DisplayShift(int pos);

unsigned int arr[8] = {0x00,0x0e,0x1f,0x1f,0x1f,0x1f,0x0e,0x00};

int cnt=1;
int flag = 1;
int i;

int main(void)
{
	
	DDRC = 0xff;
	PORTC = 0x00;
	
	LCD_INIT();
	COMMAND(0x01);
	
	COMMAND(0x40);
	_delay_ms(2);
	for(i=0;i<8;i++)
	{
		DATA(arr[i]);
	}
	
	FONT(0,0,0);
	
	while (1)
	{
		if(cnt==16)
			flag = 1;
		else if(cnt==1)
			flag = 0;
		
		if(flag == 1)
		{
			DisplayShift(1);
			cnt--;
		}
		else if(flag == 0)
		{
			DisplayShift(0);
			cnt++;
		}
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

void FONT(char address,char font,int pos)
{
	if(pos == 0)
	{
		COMMAND(0x80|0x00+address);
		DATA(font);
	}
	else if(pos == 1)
	{
		COMMAND(0x80|0x40+address);
		DATA(font);
	}
}

void DisplayShift(int pos)
{
	if(pos==0)//right
	{
		COMMAND(0x1c);
		_delay_ms(100);
	}
	else if(pos ==1)//left
	{
		COMMAND(0x18);
		_delay_ms(100);
	}
}