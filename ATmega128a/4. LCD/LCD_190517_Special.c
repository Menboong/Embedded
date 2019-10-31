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
void TIMER();

int flag=0;
int sec1=0,sec2=0,min=0;
unsigned char sec1arr[3],sec2arr[3],minarr[3];

int main(void)
{
	unsigned char string_M[] = "TIME";
	
	DDRC = 0xff;
	DDRA = 0x00;
	PORTC = 0x00;
	
	LCD_INIT();
	
	COMMAND(0b00000001);
	
	MOVE(1,7);
	STRING(string_M,4);
	
	
	
	while (1)
	{
		if(!(PINA&=0x01))
		{
			_delay_ms(30);
			flag = 1;
		}
		else if(!(PINA&=0x02))
		{
			_delay_ms(30);
			flag = 0;
		}
		else if(!(PINA&=0x04))
		{
			_delay_ms(30);
			sec1 = 0;
			sec2 = 0;
			min = 0;
			
			sprintf(sec1arr,"%d",sec1);
			sprintf(sec2arr,"%d",sec2);
			sprintf(minarr,"%d",min);
			
			MOVE(2,5);
			DATA('0');
			STRING(minarr,1);
			DATA(':');
			MOVE(2,8);
			DATA('0');
			STRING(sec2arr,1);
			DATA(':');
			MOVE(2,11);
			DATA('0');
			STRING(sec1arr,1);
		}
		
		if(flag == 1)
		{
			TIMER();
			
			sprintf(sec1arr,"%d",sec1);
			sprintf(sec2arr,"%d",sec2);
			sprintf(minarr,"%d",min);
			
			if(min<10)
			{
				MOVE(2,5);
				DATA('0');
				STRING(minarr,1);
			}
			else
			{
				MOVE(2,5);
				STRING(minarr,2);
			}
			if(sec2<10)
			{
				MOVE(2,8);
				DATA('0');
				STRING(sec2arr,1);
			}
			else
			{
				MOVE(2,8);
				STRING(sec2arr,2);
			}
			if(sec1<10)
			{
				MOVE(2,11);
				DATA('0');
				STRING(sec1arr,1);
			}
			else
			{
				MOVE(2,11);
				STRING(sec1arr,2);
			}
			
			MOVE(2,7);
			DATA(':');
			MOVE(2,10);
			DATA(':');
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

void TIMER()
{
	if(sec1 > 99)
	{
		sec1 = 0;
		if(sec2 >= 59)
		{
			sec2 = 0;
			if(min >= 59)
			{
				sec1 = 0;
				sec2 = 0;
				min = 0;
			}
			else
			min++;
		}
		else
		sec2++;
	}
	else
	sec1++;
}