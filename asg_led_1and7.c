#include<LPC21xx.h>
#include"delay.h"
#define LED_0 0
u8 i,j;
main()
{
		IODIR0|=255<<LED_0;
		IOSET0=15<<LED_0;
		for(j=0;j<5;j++)
		{
			for(i=7;i>=4;i--)
			{
			IOPIN0=(IOPIN0&(~(255))) | (((1<<i)|(1<<(7-i)))^0x0f);
			delay_ms(100);
			}
		}
	while(1);
}
