#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	DDRA = 0x00;
	DDRC = 0xFF;
	
	int random;
    int arr[6] = {0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D};
    while (1)
    {	
		srand(time(NULL));
		
		while(!(PINA &= 0x01))
		{
			random = rand () % 6;
		
			PORTC = arr[random];
			_delay_ms(50);
	   }
	}
}

