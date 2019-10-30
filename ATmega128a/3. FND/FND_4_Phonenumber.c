#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

int arr[17] = {0xff,0xff,0xff,0xc0,0xf9,0xc0,0xbf,0xa4,0xc0,0x80,0x83,0xbf,0xf8,0xf9,0xc0,0x92,0xff};
unsigned long long int milsec;

int main(void)
{
	int i,j;
	DDRG = 0xff;
	DDRC = 0xff;
	
	i = 0;
    while (1) 
    {
		for(j=0;j<4;j++)
		{
			PORTG = 0x01 << j;
			PORTC = arr[(i+j)%17];
			_delay_ms(1);
			milsec++;
		}
		if(milsec%500 == 0)
			i++;
		
	}
}

