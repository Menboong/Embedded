#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18, 0x20, 0x03, 0x27, 0x21, 0x04, 0x0E};
	int cnt1=0,cnt2=0;
	
	DDRA = 0x00;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRG = 0xFF;
	
	PORTG = 0xFF;
	PORTC = 0x40;
	PORTD = 0x40;
    while (1) 
    {
		if(!(PINA &= 0x01))
		{
			_delay_ms(300);
			
			PORTD = arr[cnt1];
			PORTC = arr[cnt2];
			
			
			if(cnt1 == 0)
			{
				if(cnt2 == 0)
					cnt2 = 15;
				else
					cnt2--;
				cnt1 = 15;
			}
			else
				cnt1--;
			
		}
		else if(!(PINA &= 0x02))
		{
			_delay_ms(300);
		
			PORTD = arr[cnt1];
			PORTC = arr[cnt2];
		
			if(cnt1 == 15)
			{
				cnt1 = 0;
				if(cnt2 == 15)
					cnt2 = 0;
				else
					cnt2++;
			}
			else
				cnt1++;
			
		}
		else if(!(PINA &= 0x04))
		{
			_delay_ms(30);
			cnt1 = 0;
			cnt2 = 0;
			PORTC = arr[cnt1];
			PORTD = arr[cnt2];
		}
	}
}

