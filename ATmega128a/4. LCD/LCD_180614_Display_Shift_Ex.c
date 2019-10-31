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
void lcd_print(char* arr,int size,char addr);

unsigned int arr[5][8] ={{0x00,0x0a,0x04,0x04,0x11,0x0e,0x00,0x00},	//웃음
						 {0x08,0x1d,0x09,0x15,0x01,0x09,0x1f,0x00},	//최
						 {0x04,0x0a,0x11,0x11,0x04,0x04,0x1f,0x00},	//소
						 {0x01,0x0b,0x15,0x0b,0x01,0x04,0x0a,0x04},//영
					     {0x00,0x0a,0x04,0x04,0x11,0x0e,0x00,0x00}};
unsigned char france[17] = {'J','e',' ', 'm','\'','a','p','p','e','l','l','e',0,1,2,3,4};

int pos=0;
int flag = 0;
int i,j;

int main(void)
{
	
	DDRC = 0xff;
	DDRB = 0xff;
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
		
	i = 0;
	j = 0;
	
	while(1)
	{	
		if(pos==0x50)
		{
			pos = 0x00;
		}
		if(pos==0x10)
		{
			pos = 0x40;
		}
		lcd_print(france,sizeof(france),pos);
		pos++;
		_delay_ms(500);
		COMMAND(0x01);
	}
}
void lcd_print(char* arr,int size,char addr)
{
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
		_delay_ms(500);
	}
	else if(pos ==1)//left
	{
		COMMAND(0x18);
		_delay_ms(500);
	}
}