#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int random1,random2;
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18, 0x20, 0x03, 0x27, 0x21, 0x04, 0x0E};
	
	DDRA = 0x00;
	DDRC = 0xff;
	DDRD = 0xff;
	DDRG = 0xff;
	
	PORTG = 0xff;
    while (1) 
    {
		srand(time(NULL));
		
		while(!(PINA &= 0x01))
		{
			random1 = rand() % 15;
			random2 = rand() % 15;
			
			PORTC = arr[random1];
			PORTD = arr[random2];
			_delay_ms(50);
		}
    }
}

