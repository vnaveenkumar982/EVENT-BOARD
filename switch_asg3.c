#include<LPC21xx.h>
#include"delay.h"
#define SW_4 4
#define SW_5 5
#define LED_AL_7 7
main()
{
		IODIR0|=1<<LED_AL_7;
		while(1)
		{
			if((((IOPIN0>>SW_4)&1)==0) && (((IOPIN0>>SW_5)&1)==0))
			IOCLR0=1<<LED_AL_7;
			else
			IOSET0=1<<LED_AL_7;
		}
}
