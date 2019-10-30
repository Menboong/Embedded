#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int sc=0,sec1=0,sec2=0,sec3=0,min1=0;
int cnt=0;
int FNDPlaceCnt=0;
int arr[16] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x03, 0x78, 0x00, 0x18};
int arr2[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x83, 0xf8, 0x80, 0x98};
int flag=0;

void FND_Display()
{
	switch(FNDPlaceCnt)
	{
		case 0:
			PORTG = 0x08;
			PORTC = arr2[sec1];
			break;
		case 1:
			PORTG = 0x04;
			PORTC = arr[sec2];
			break;
		case 2:
			PORTG = 0x02;
			PORTC = arr2[sec3];
			break;
		case 3:
			PORTG = 0x01;
			PORTC = arr[min1];
			break;
	}
	
}

int main(void)
{
	DDRG = 0xFF;
	DDRC = 0xFF;
	DDRA = 0x00;
	
	while (1)
	{
		if(!(PINA &= 0x01))
		{
			flag = 1;
			sc = 0;
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
		
		_delay_ms(1);
		FND_Display();
		if(flag == 1)
		{	
			sc++;
			if(sc >= 1000)
			{
				sc = 0;
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
			else
				sc++;
		}
		if(cnt == 3)
		{
			if(FNDPlaceCnt == 4)
			FNDPlaceCnt = 0;
			else
			FNDPlaceCnt++;
			cnt = 0;
		}
		else
		cnt++;
	}
}
