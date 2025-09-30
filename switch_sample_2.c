/*#include<LPC21xx.h>
#define LED_0 0
#define SW_16 16
int cnt=0;
main()
{
	IODIR0|=255<<LED_0;
	IOSET0=15<<LED_0;
	while(1)
	{
		if(((IOPIN0>>SW_16)&1)==0)
		{
			cnt++;
			IOPIN0=(IOPIN0&(~(255<<LED_0))) |((cnt^0x0f)<<LED_0);
			while(((IOPIN0>>SW_16)&1)==0);
		}
	}
}
#include<LPC22xx.h>
#include"delay.h"
#define LED_0 0
#define SW_16 16
#define SW_17 17
unsigned int cnt=0;
main()
{
        IODIR0|=255<<LED_0;
        IOSET0=15<<LED_0;
        while(1)
        {
                if(((IOPIN0>>SW_16)&1)==0)
                {       if(cnt<255)
                        {
                        cnt++;
                        }
                        IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((cnt^0X0F)<<LED_0) ;
                        delay_s(1);
                }
                else if(((IOPIN0>>SW_17)&1)==0)
                {
                        if(cnt>=1)
                        {
                        cnt--;
                        }
                        IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((cnt^0X0F)<<LED_0) ;
                        delay_s(1);
                }
        }

}*/
#include"delay.h"
#include<LPC21xx.h>
#define LED_0 0
#define SW_16 16
#define SW_17 17
unsigned int cnt=0;
main()
{
        IODIR0|=255<<LED_0;
        IOSET0=15<<LED_0;
        while(1)
        {
                if(((IOPIN0>>SW_16)&1)==0)
                {       if(cnt<255)
                        {
                        cnt++;
                        }
                        IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((cnt^0X0F)<<LED_0) ;
												delay_ms(100);
                        //while(((IOPIN0>>SW_16)&1)==0);
                }
                else if(((IOPIN0>>SW_17)&1)==0)
                {
                        if(cnt>=1)
                        {
                        cnt--;
                        }
                        IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((cnt^0X0F)<<LED_0) ;
												delay_ms(100);
                        //while(((IOPIN0>>SW_17)&1)==0);

                }
        }

}


