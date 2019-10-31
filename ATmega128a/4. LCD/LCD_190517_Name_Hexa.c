#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void STRING(unsigned char font[], unsigned char n);

int main(void)
{
	DDRC = 0xff;
	DDRD = 0xff;
	PORTC = 0x00;
	PORTD = 0x00;
	LCD_INIT();
	
	DATA(0x43);
	_delay_ms(50);
	DATA(0x68);
	_delay_ms(50);
	DATA(0x6f);
	_delay_ms(50);
	DATA(0x69);
	_delay_ms(50);
	DATA(0xfe);
	_delay_ms(50);
	DATA(0x53);
	_delay_ms(50);
	DATA(0x6f);
	_delay_ms(50);
	DATA(0x79);
	_delay_ms(50);
	DATA(0x6f);
	_delay_ms(50);
	DATA(0x75);
	_delay_ms(50);
	DATA(0x6e);
	_delay_ms(50);
	DATA(0x67);
	_delay_ms(50);
	while (1)
	{
		
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
	int i
}