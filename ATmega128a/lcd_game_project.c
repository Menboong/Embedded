#define F_CPU 16000000UL
#define CLEAR 0x01

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void CGRAM_INIT(void);
void LINE_INIT(void);
void MOVE(int y, int x);
void LCD_PRINT(unsigned char* arr,int size,char addr);
void FILL_ARR(unsigned char* arr,int size);

unsigned int data[4][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},		//빈벽돌
						  {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},		//벽돌
						  {0x17,0x15,0x0a,0x0f,0x14,0x1b,0x03,0x14},		//부셔진벽돌
						  {0x06,0x06,0x1f,0x14,0x04,0x1f,0x11,0x00}};		//사람
unsigned char line1[15];
unsigned char line2[15];
unsigned char person[1] = {3};
unsigned char word[] = "press button";
unsigned char word2[] = "to start";
				
int i,j;
int flag = 0;
int perpos = 1;		//캐릭터의 현재 줄 위치  
int main(void)
{
	
	DDRC = 0xff;
	DDRD = 0x00;
	DDRG = 0xff;

	PORTC = 0x00;
	
	//lcd초기설정
	LCD_INIT();
	COMMAND(CLEAR);
	CGRAM_INIT();
	srand(4);
	
	while(1)
	{
		LINE_INIT();
		if(!(PIND&0x04))
		{
			flag = 1;
			PORTG = 0xff;
		}
		else
		{
			LCD_PRINT(word,12,0x02);
			LCD_PRINT(word2,8,0x44);
		}
		
		_delay_ms(200);
		while(flag!=0)
		{
			if(!(PIND&=0x01))
			{
				perpos = 1;
			}
			else if(!(PIND&=0x02))
			{
				perpos = 2;
			}
		
			if(line1[0] == 1)
			{
				if(perpos == 1)
				{
					if(!(PIND&=0x04))
					{
						line1[0] = 2;
						LCD_PRINT(line1,15,0x01);
						_delay_ms(100);
						line1[0] = 0;
						LCD_PRINT(line1,15,0x01);
					}
					else
						flag = 0;
				}
			}
			if(line2[0] == 1)
			{
				if(perpos == 2)
				{
					if(!(PIND&=0x04))
					{
						line2[0] = 2;
						LCD_PRINT(line2,15,0x01);
						_delay_ms(100);
						line2[0] = 0;
						LCD_PRINT(line2,15,0x01);
					}
					else
						flag = 0;
				}
			}
		
			if(perpos == 1)
				LCD_PRINT(person,1,0x00);
			else if(perpos == 2)
				LCD_PRINT(person,1,0x40);
			
			FILL_ARR(line1,15);
			LCD_PRINT(line1,14,0x01);
			FILL_ARR(line2,15);
			LCD_PRINT(line2,14,0x41);
			_delay_ms(1500);
			COMMAND(CLEAR);
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

void CGRAM_INIT(void)
{
	unsigned int cgraminit[64] = {0};
	
	COMMAND(0x40);
	_delay_ms(2);
	for(i=0;i<64;i++)
		DATA(cgraminit[i]);
	
	COMMAND(0x40);
	_delay_ms(2);
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
			DATA(data[i][j]);
	}
}

void LINE_INIT(void)
{
	for(i=0;i<15;i++)
	{
		line1[i] = 0;
		line2[i] = 0;
	}
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

void LCD_PRINT(unsigned char* arr,int size,char addr)
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

void FILL_ARR(int size)
{
	arr[size-1]=rand()%2;
	
	for(i=0;i<size;i++)
	{
		arr[i] = arr[i+1];
	}
}