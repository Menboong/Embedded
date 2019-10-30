#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	DDRA = 0x00;
	DDRC = 0xFF;
	
	int arr[10] = {0x3F, 0x30, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x6F};
    int pos=0;
	
	while (1) 
    {
		if(!(PINA &= 0x01))
		{
			if(pos == 0)
				pos = 9;
			else
				pos--;
				
			PORTC = arr[pos];
			_delay_ms(300);
		}
		else if(!(PINA &= 0x02))
		{
			if(pos == 9)
				pos = 0;
			else
				pos++;
				
			PORTC = arr[pos];
			_delay_ms(300);
		}
		else if(!(PINA &= 0x04))
		{
			pos = 0;
			PORTC = arr[pos];
			_delay_ms(300);
		}
		
    }
}

