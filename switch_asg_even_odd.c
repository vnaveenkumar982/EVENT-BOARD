#include<LPC21xx.h>
#include"delay.h"
#define LED_0 0
#define SW_16 16
#define SW_17 17
int i,res;
main()
{
	IODIR0|=255<<LED_0;
	IOSET0=15<<LED_0;
	while(1)
	{
		if(((IOPIN0>>SW_16)&1)==0)
		{
		for(i=0;i<255;i++)
		{
				if(((IOPIN0>>SW_17)&1)==0)
				break;
					 	if(i%2==0)
							{
										IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((i^0x0f)<<LED_0);
										delay_ms(100);
							}
		}
		}
		else if(((IOPIN0>>SW_17)&1)==0)
		{
		for(i=0;i<255;i++)
		{
				if(((IOPIN0>>SW_16)&1)==0)
				break;
					 	if(i%2==1)
							{
										IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((i^0x0f)<<LED_0);
										delay_ms(100);
							}
		}
		if(i>255)
		{
			i=0;
		}
	}
	}
	
}
