#include"types.h"
#include<LPC21XX.h>
#include"pin_connect_block.h"
void cfgportpin(u32 portno,s32 pinno,u32 pinfunc)
{
        if(portno==0)
        {
                if((pinno>=0) && (pinno<=15))
                {
                        PINSEL0=((PINSEL0&~(3<<(pinno*2))) | (pinfunc<<(pinno*2)));
                }
                else if((pinno>=16) && (pinno<=31))
                {
                        PINSEL1=((PINSEL1&~(3<<((pinno-16)*2))) | (pinfunc<<((pinno-16)*2)));
                }
        }
}
