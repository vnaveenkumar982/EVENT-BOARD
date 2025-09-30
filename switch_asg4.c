 
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
			(((IOPIN0>>SW_4)&3)<3)?(IOCLR0=1<<LED_AL_7):(IOSET0=1<<LED_AL_7);
		}
}
