/*
 * RGBLED.c
 *
 * Created: 2019-11-27 오전 9:26:43
 * Author : 2314
 */ 
#define F_CPU 16000000ul

#include <avr/io.h>
#include <util/delay.h>


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

void PWM_INIT()
{
	DDRB = 0XFF;
	TCCR0 = (1<<WGM00) | (1<<COM01);
	TCCR1A = (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1);
	TCCR1B = (1<<WGM13) | (1<<CS10);
	ICR1 = 255;
	OCR1A = 0;
	OCR1B = 0;
	OCR1C = 0;
}

void ADC_INIT()
{
	DDRF = 0X00;
	ADMUX = (1<<REFS0)|(1<<ADLAR); //0b01100000
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
}
uint16_t ADC_READ(uint8_t ch) {
	
	ch = ch&0x07;
	ADMUX&=0x70;
	ADMUX|=ch;
	
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	return(ADCH);
	
}

int main(void)
{
	PWM_INIT();
	ADC_INIT();
	LCD_INIT();
	
	char val[10];
	int data;
	/* Replace with your application code */
	while (1)
	{
		data = ADC_READ(1);
		sprintf(val,"%d",data);
		LCD_PRINT(val,3,0x00);
		
		data = ADC_READ(2);
		sprintf(val,"%d",data);
		LCD_PRINT(val,3,0x04);
		
		data = ADC_READ(3);
		sprintf(val,"%d",data);
		LCD_PRINT(val,3,0x09);
		
		OCR1A=ADC_READ(1);
		OCR1B=ADC_READ(2);
		OCR1C=ADC_READ(3);
	}
}




