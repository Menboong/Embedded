#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18, 0x20, 0x03, 0x27, 0x21, 0x04, 0x0E};
	int i,j;
	
	DDRA = 0xFF;
	DDRE = 0xFF;
	DDRG = 0xff;
	PORTG = 0xff;
	
	while(1)
	{
		PORTA = 0x40;
		PORTE = 0X40;
		/*for(i=0;i<16;i++)
		{
		PORTF = arr[i];
		_delay_ms(500);
		}*/
	}
}
