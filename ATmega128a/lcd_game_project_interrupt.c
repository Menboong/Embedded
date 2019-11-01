#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#define CLEAR 0x01

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void CGRAM_INIT(void);
void LINE_INIT(void);
void FND_INIT(void);
void LCD_PRINT(unsigned char* arr,int size,char addr);
void FILL_ARR(unsigned char* arr,int size);
void TIME_CONTROL(void);
void FND_PRINT(void);
ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);

unsigned int data[4][8] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},		//빈벽돌
{0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},		//벽돌
{0x17,0x15,0x0a,0x0f,0x14,0x1b,0x03,0x14},		//부셔진벽돌
{0x06,0x06,0x1f,0x14,0x04,0x1f,0x11,0x00}};		//사람
int num[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18};
unsigned char line1[15];
unsigned char line2[15];
unsigned char person[1] = {3};
unsigned char word[] = "press button";
unsigned char word2[] = "to start";
unsigned char word3[] = "clear!!";

int i,j;
int flag = 0;
int perpos = 1;		//캐릭터의 현재 줄 위치
int atk1,atk2;
int sec = 1000;
int cnt = 0;
int sco = 0;

int main(void)
{
	DDRA = 0xff;
	DDRC = 0xff;
	DDRD = 0x00;
	DDRE = 0xff;
	DDRG = 0xff;
	
	PORTE = 0x00;
	
	EICRA = 0x02;
	
	sei();
	
	//lcd초기설정
	LCD_INIT();
	COMMAND(CLEAR);
	CGRAM_INIT();
	srand(4);
	
	while(1)
	{	
		EIMSK = 0x00;
		LINE_INIT();
		FND_INIT();
		sec = 1000;
		sco = 0;
		
		if(!(PIND&0x04))
			flag = 1;
		else
		{
			LCD_PRINT(word,12,0x02);
			LCD_PRINT(word2,8,0x44);
		}
		
		if(flag == 1)
			PORTG = 0x07;
		else
			PORTG = 0x03;
		
		_delay_ms(200);
		
		while(flag!=0)
		{	
			EIMSK = 0x07;
			
			if(sco == 99)
			{
				COMMAND(CLEAR);
				LCD_PRINT(word3,7,0x05);
				_delay_ms(2000);
				flag = 0;
			}
			
			if(line1[0] == 1)
			{
				if(perpos == 1)
					flag = 0;
			}
			if(line2[0] == 1)
			{
				if(perpos == 2)
					flag = 0;
			}
			
			if(perpos == 1)
				LCD_PRINT(person,1,0x00);
			else if(perpos == 2)
				LCD_PRINT(person,1,0x40);
			
			FILL_ARR(line1,15);
			FILL_ARR(line2,15);
			
			LCD_PRINT(line1,14,0x01);
			LCD_PRINT(line2,14,0x41);
			FND_PRINT();
			
			TIME_CONTROL();
			_delay_ms(sec);
			COMMAND(CLEAR);
		}
	}
}

void COMMAND(unsigned char byte) // 명령어 함수
{
	_delay_ms(2);
	PORTE = byte&0xf0;	//명령어쓰기
	PORTE &= 0b11111100;	//RS=0, RW=0, 명령어를 쓰도록 설정
	_delay_us(1);			//RS & RW setup time
	PORTE |= 0b00000100;	//E = 1, lcd동작
	_delay_us(1);			//E pulse width time
	PORTE &= 0b11111011;	//E=0
	
	PORTE = (byte<<4)&0xf0; //명령어쓰기
	PORTE &= 0b11111100;	//RS =0, RW =0 명령어를 쓰도록 설정
	_delay_us(1);
	PORTE |= 0b00000100;	//E=1 lcd동작
	_delay_us(1);
	PORTE &= 0b11111011;	//E=0
}
void DATA(unsigned char byte)
{
	_delay_ms(2);
	PORTE = byte&0xf0;		//상위 4비트 쓰기
	PORTE |= 0b00000001;
	PORTE &= 0b11111101;	//RS,RW설정
	_delay_us(1);
	PORTE |= 0b00000100;	//E=1, lcd동작
	_delay_us(1);
	PORTE &= 0b11111011;	//E=0
	
	PORTE = (byte<<4)&0xf0;	//하위 4비트 쓰기
	PORTE |= 0b00000001;
	PORTE &= 0b11111101;	//RS,RW설정
	_delay_us(1);
	PORTE |= 0b00000100;	//E=1, lcd동작
	_delay_us(1);
	PORTE &= 0b11111011;	//E=0
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
void FND_INIT(void)
{
	PORTC = 0xff;
	PORTA = 0xff;
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
void FILL_ARR(unsigned char* arr,int size)
{
	arr[size-1]=rand()%2;
	
	for(i=0;i<size;i++)
	{
		arr[i] = arr[i+1];
	}
}
void TIME_CONTROL(void)
{
	if(sec>200)
	{
		if(cnt == 2)
		{
			sec -= 10;
			cnt = 0;
		}
		else
			cnt++;
	}
}
void FND_PRINT(void)
{
	PORTA = num[sco/10];
	PORTC = num[sco%10];
}

ISR(INT0_vect)
{
	perpos = 1;
}
ISR(INT1_vect)
{
	perpos = 2;
}
ISR(INT2_vect)
{
	_delay_ms(30);
	if(perpos == 1)
	{
		if(line1[0]==1)
		{
			line1[0] = 2;
			LCD_PRINT(line1,14,0x01);
			_delay_ms(100);
			line1[0] = 0;
			LCD_PRINT(line1,14,0x01);
			sco++;
		}
	}
	if(perpos == 2)
	{
		if(line2[0]==1)
		{
			line2[0] = 2;
			LCD_PRINT(line2,14,0x41);
			_delay_ms(100);
			line2[0] = 0;
			LCD_PRINT(line2,14,0x41);
			sco++;
		}
	}
}