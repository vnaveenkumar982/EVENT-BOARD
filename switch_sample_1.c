#include<LPC21xx.h>
#define LED_0 0
#define SW_16 16
#define SW_17 17
#define SW_18 18
#define SW_19 19
main()
{
	IODIR0|=255<<LED_0;
		IOSET0=15<<LED_0;
	while(1)
	{
		if(((IOPIN0>>SW_16)&1)==0)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((((1<<0)|(1<<7))^0x0f))<<LED_0;
			while(((IOPIN0>>SW_16)&1)==0);
		}
		else if(((IOPIN0>>SW_17)&1)==0)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((((1<<1)|(1<<6))^0x0f))<<LED_0;
			while(((IOPIN0>>SW_17)&1)==0);
		}
		else if(((IOPIN0>>SW_18)&1)==0)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((((1<<2)|(1<<5))^0x0f))<<LED_0;
			while(((IOPIN0>>SW_18)&1)==0);
		}
		else if(((IOPIN0>>SW_19)&1)==0)
		{
			IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((((1<<3)|(1<<4))^0x0f))<<LED_0;
			while(((IOPIN0>>SW_19)&1)==0);
		}
	}
}
