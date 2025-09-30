#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#define LED_AH_7 7
#define SW_AH_4 4
int main()
{
	IODIR0|=1<<LED_AH_7;
	while(1)
	{
	if(!(((IOPIN0>>SW_AH_4)&1)==0))
		IOCLR0=1<<LED_AH_7;
	else
		IOSET0=1<<LED_AH_7;	
	}
}
