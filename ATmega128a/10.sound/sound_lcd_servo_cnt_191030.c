#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void LCD_INIT(void);
void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_PRINT(unsigned char* arr,int size,char addr);
void Timer_Init(void);

int main(void)
{
	int cnt = 0;
	int arr[1];

	DDRB = 0XfF;
	
	DDRD = 0X00;
	PORTD = 0XFF;
	
	LCD_INIT();
	COMMAND(0X01);
	
	Timer_Init();
	
	while (1)
	{
		if(!(PIND&0x01))
		cnt = 0;
		
		if(!(PIND&0X02))
		{
			_delay_ms(50);
			cnt++;
			COMMAND(0x01);
		}
		
		if(cnt%10==4)
			OCR1A = 500;
		else if(cnt%10==9)
			OCR1A = 250;
		else if(cnt%10==0)
			OCR1A = 375;
		
		sprintf(arr,"%d",cnt);
		if(cnt<10)
			LCD_PRINT(arr,1,0x03);
		else if(cnt<100)
			LCD_PRINT(arr,2,0x03);
		else if(cnt<1000)
			LCD_PRINT(arr,3,0x03);
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

void Timer_Init()
{
	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	ICR1 = 4999;
	OCR1A =	375;	//  0도) 20:1.5 = 4999:x = 375   90도) 20:2 = 4999:x = 500  -90도) 20:1 = 4999:x = 250
	TCNT1 = 0X00;
}