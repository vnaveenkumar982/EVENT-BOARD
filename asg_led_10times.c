#include<LPC21xx.h>
#include"delay.h"
#define LED_0 0
u32 i; 
main()
{
	IODIR0|=255<<LED_0;
	IOPIN0|=15<<LED_0;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			IOPIN0|=(i^0x0f)<<LED_0;
			delay_s(1);
			IOPIN0&=(~i^0x0f)<<LED_0;
		}	
	}
}
