#include<LPC21xx.h>
#include"delay.h"
#include"types.h"
#define CA7SEG 8
#define DSEL1 16
#define DSEL2 17
const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};
void disp_2mux(u8 n,u8 segno);
s32 i,dly;
int main()
{
	IODIR0|=255<<CA7SEG;
	IODIR0|=1<<DSEL1|1<<DSEL2;
		for(i=0;i<=9;i++)
		{
			if(i%2==0)
			{
			for(dly=50;dly>0;dly--)
			{
				disp_2mux(i,0);
			}
			}
		}
		for(i=9;i>=0;i--)
		{
			if(i%2==1)
			{
			for(dly=50;dly>0;dly--)
			{
				disp_2mux(i,1);
			}
		}
		}
	while(1);	
}

void disp_2mux(u8 n, u8 segno)
{
    IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n] << CA7SEG);

    if(segno==0)
    {
        IOSET0=1 << DSEL1;
        delay_ms(5);
        IOCLR0=1 << DSEL1;
    }
    else if(segno==1) 
    {
        IOSET0=1<<DSEL2;
        delay_ms(5);
        IOCLR0=1<<DSEL2;
    }
}

