#include<LPC21xx.h>
#include"delay.h"
#define LED_0 0
u8 i;
main()
{
	IODIR0|=255<<LED_0;
	IOPIN0|=15<<LED_0;
	while(1)
	{
		for(i=7;i>0;i--)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | (((1<<i)^0x0f)<<LED_0);
			delay_ms(200);
		}
		for(i=0;i<7;i++)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | (((1<<i)^0x0f)<<LED_0);
			delay_ms(200);
		}
		
		
	}
	
	
}
