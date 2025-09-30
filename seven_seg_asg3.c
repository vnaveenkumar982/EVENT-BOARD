/*#include<LPC21xx.h>
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
void disp_2mux(u8 n);
s32 i,dly;
int main()
{
	IODIR0|=255<<CA7SEG;
	IODIR0|=1<<DSEL1|1<<DSEL2;
		for(i=0;i<=99;++i)
		{
			for(dly=10;dly>0;dly--)
			{
				disp_2mux(i);
			}
		}

	while(1);	
}

void disp_2mux(u8 n)
{
     IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (((seglut[n/10])&0x7f) << CA7SEG);

        IOSET0=1 << DSEL1;
        delay_ms(1);
        IOCLR0=1 << DSEL1;
  
	    IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n%10] << CA7SEG);

        IOSET0=1<<DSEL2;
        delay_ms(1);
        IOCLR0=1<<DSEL2;
}


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
void disp_2mux(u8 n);
s32 i,dly;
int main()
{
	IODIR0|=255<<CA7SEG;
	IODIR0|=1<<DSEL1|1<<DSEL2;
		for(i=0;i<=99;++i)
		{
			for(dly=20;dly>0;dly--)
			{
				disp_2mux(i);
			}
		}
		for(i=99;i>=0;i--)
		{
			for(dly=20;dly>0;dly--)
			{
				disp_2mux(i);
			}
		}


	while(1);	
}

void disp_2mux(u8 n)
{
     IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n/10] << CA7SEG);

        IOSET0=1 << DSEL1;
        delay_ms(1);
        IOCLR0=1 << DSEL1;
  
	    IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n%10] << CA7SEG);

        IOSET0=1<<DSEL2;
        delay_ms(1);
        IOCLR0=1<<DSEL2;
}

*/

#include<LPC21xx.h>
#include"delay.h"
#include"types.h"
#define CA7SEG 8
#define DSEL1 16
#define DSEL2 17
#define SW1 1
#define SW2 2
const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};
void disp_2mux(u8 n);
s32 cnt=0;

int main()
{
	IODIR0|=255<<CA7SEG;
	IODIR0|=1<<DSEL1|1<<DSEL2;
	while(1)
	{
		if(((IOPIN0>>SW1)&1)==0)
		{
			cnt++;
			disp_2mux(cnt);
			while(((IOPIN0>>SW1)&1)==0);
		}
		else if(((IOPIN0>>SW2)&1)==0)
		{
			cnt--;
			disp_2mux(cnt);
			while(((IOPIN0>>SW2)&1)==0);
		}
		if(cnt<0)
			cnt=0;
		else if(cnt>99)
			cnt=99;
}
}
void disp_2mux(u8 n)
{
     IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n/10] << CA7SEG);

        IOSET0=1 << DSEL1;
        delay_ms(1);
        IOCLR0=1 << DSEL1;
  
	    IOPIN0=(IOPIN0 & ~(255 << CA7SEG)) | (seglut[n%10] << CA7SEG);

        IOSET0=1<<DSEL2;
        delay_ms(1);
        IOCLR0=1<<DSEL2;
}



