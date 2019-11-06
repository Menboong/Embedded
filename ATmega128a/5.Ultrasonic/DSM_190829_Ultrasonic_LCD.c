#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void STRING(unsigned char font[], unsigned char n);
void MOVE(int y, int x);
void LCD_PRINT(unsigned char* arr,int size,char addr);
void CGRAM_INIT(void);

unsigned int i=0,j;

unsigned char block[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
unsigned char eng[] = "distance: ";
unsigned char cm[] = "cm";
unsigned int distance;
unsigned char val[6];
unsigned char upper[5],lower[5];
unsigned char bar[10] = {0};
unsigned int i;

int main(void)
{
	
	DDRC = 0xff;
	DDRD = 0xff;
	DDRE = ((DDRE|(1<<TRIG))&~(1<<ECHO));
	
	PORTC = 0x00;
	
	CGRAM_INIT();
	LCD_INIT();

	COMMAND(0x01);
	
	COMMAND(0x40);
	_delay_ms(2);
	
	MOVE(1,1);
	
	
	while (1)
	{
		TCCR1B = 0X03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE&(1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE&(1<<ECHO));
		TCCR1B = 0x00;
		distance = SOUND_VELOCITY * (TCNT1 * 4/2)/1000;
		distance = distance/10;		
		
		sprintf(val,"%d",distance);
		
		LCD_PRINT(eng,10,0x00);
		LCD_PRINT(cm,2,0x0e);
		
		if(distance<10)
		{
			MOVE(1,16);
			LCD_PRINT(val,1,0x0d);	
		}
		else if(distance<100)
		{
			MOVE(1,15);
			LCD_PRINT(val,2,0x0c);;
		}
		else if(distance<1000)
		{
			MOVE(1,14);
			LCD_PRINT(val,3,0x0b);
		}
		
		for(i=0;i<10;i++)
			bar[i] = 0;
		for(i=0;i<distance/10;i++)
			bar[i] = 1;
		
		LCD_PRINT(bar,10,0x41);
		
		COMMAND(0x01);
		
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

void CGRAM_INIT(void)
{
	unsigned int cgraminit[64] = {0};
	
	COMMAND(0x40);
	_delay_ms(2);
	for(i=0;i<16;i++)
	{
		DATA(cgraminit[i]);
	}
	
	COMMAND(0x40);
	_delay_ms(2);
	for(i=0;i<16;i++)
	{
		DATA(block[i]);
	}
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