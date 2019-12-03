#define F_CPU 16000000ul

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DHT11_PIN 4

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void LCD_PRINT(unsigned char* arr,int size,char addr);

void Request();
void Response();
uint8_t Receive_Data();

void FND_Display();

uint8_t c=0;
uint8_t Humi_L,Humi_D;
uint8_t Temp_L,Temp_D;
uint8_t CheckSum;
int FND_Place_Cnt=0;
int sec = 0;
uint8_t arr[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18};

int main(void)
{	
	DDRA = 0XFF;
	DDRB = 0xFF;
	DDRC = 0xff;
	DDRG = 0XFF;
	
	PORTA = 0X00;
	PORTB = 0XFF;
	PORTG = 0X00;
	
	char data[5];
	char error[14] = "checksum error";
	char period[1] = ".";
	char C[1] = "C";
	char H[1] = "%";
	
	LCD_INIT();
	COMMAND(0x01);
	
    while(1) 
    {
		COMMAND(0x01);
		
		Request();									//start_pulse
		Response();									//response_pulse
				
		Humi_L = Receive_Data();					//Humi_L
		Humi_D = Receive_Data();					//Humi_D
		Temp_L = Receive_Data();					//Temp_L
		Temp_D = Receive_Data();					//Temp_D
		CheckSum = Receive_Data();					//CheckSum
		if((Humi_L+Humi_D+Temp_D+Temp_L) != CheckSum)	//CheckSum 확인
			LCD_PRINT(error,14,0x41);
		else
		{
			itoa(Humi_L,data,10);
			LCD_PRINT(data,2,0x01);
			LCD_PRINT(period,1,0x03);
			itoa(Humi_D,data,10);
			LCD_PRINT(data,2,0x04);
			LCD_PRINT(H,1,0x06);
			
			itoa(Temp_L,data,10);
			LCD_PRINT(data,2,0x41);
			LCD_PRINT(period,1,0x43);
			itoa(Temp_D,data,10);
			LCD_PRINT(data,2,0x44);
			LCD_PRINT(C,1,0x46);
			
			itoa(CheckSum,data,10);
			LCD_PRINT(data,3,0x49);
		}
		
		while(1)
		{
			FND_Display();
			if(FND_Place_Cnt==4)
				FND_Place_Cnt = 0;
			else
				FND_Place_Cnt++;
			_delay_ms(2);
		}
	}
}

void Request()
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);
	_delay_ms(18);
	PORTD |= (1<<DHT11_PIN);
}
void Response()
{
	
	DDRD &= ~(1<<DHT11_PIN);
	
	while(PIND&(1<<DHT11_PIN));
	while((PIND&(1<<DHT11_PIN))==0);
	while(PIND&(1<<DHT11_PIN));
	
}
uint8_t Receive_Data()
{
	for(int b=0;b<8;b++)
	{	
		while((PIND & (1<<DHT11_PIN)) == 0);
		_delay_us(35);
		if(PIND & (1<<DHT11_PIN))
			c = (c<<1)|(0x01); //00000110
		else
			c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

void FND_Display()
{
	switch(FND_Place_Cnt)
	{
		case 0:
			PORTG = 0x01;
			PORTB = arr[Humi_L/10] | 0X80;
			break;
		case 1:
			PORTG = 0x02;
			PORTB = arr[Humi_L%10];
			break;
		case 2:
			PORTG = 0x04;
			PORTB = arr[Humi_D/10] | 0X80;
			break;
		case 3:
			PORTG = 0x08;
			PORTB = arr[Humi_D%10] | 0X80;
			break;
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