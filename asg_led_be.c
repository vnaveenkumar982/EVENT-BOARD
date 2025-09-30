//////ALAH//////
#include<LPC21xx.h>
#include"delay.h"
#define LED_0 0
u32 i;
main()
{
		IODIR0|=255<<LED_0;
		for(i=0;i<=255;i++)
		{
			
			IOPIN0=(IOPIN0&(~(255<<LED_0)))|((i^0X0F)<<LED_0);
			delay_ms(10);
			
		}
		while(1);
	
}

