#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

int arr[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18};
int arr2[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8, 0x80, 0x98};
unsigned long long int milsec;
int sec1=0,sec2=0,sec3=0,min1=0;

int main(void)
{
	int j,flag=0;
	DDRG = 0xff;
	DDRC = 0xff;
	
	while (1)
	{
		if(!(PINA &= 0x01))
		{
			flag = 1;
			milsec = 0;
		}
		else if(!(PINA&=0x02))
			flag = 0;
		else if(!(PINA&=0x04))
		{
			sec1 = 0;
			sec2 = 0;
			sec3 = 0;
			min1 = 0;
		}
		
		for(j=0;j<4;j++)
		{
			PORTG = 0x01 << j;
			if(j==0)
				PORTC = arr[min1];
			else if(j==1)
				PORTC = arr2[sec3];
			else if(j==2)
				PORTC = arr[sec2];
			else if(j==3)
				PORTC = arr2[sec1];
			
			_delay_ms(1);
			milsec++;
		}
		
		if(flag == 1)
		{
			if(milsec%100 == 0)
			{
				if(sec1 == 9)
				{
					sec1 = 0;
					if(sec2 == 9)
					{
						sec2 = 0;
						if(sec3 == 5)
						{
							sec3 = 0;
							if(min1 == 9)
							{
								sec1 = 0;
								sec2 = 0;
								sec3 = 0;
								min1 = 0;
							}
							else
								min1++;
						}
						else
							sec3++;
					}
					else
						sec2++;
				}
				else
					sec1++;
			}
		}
	}
}

