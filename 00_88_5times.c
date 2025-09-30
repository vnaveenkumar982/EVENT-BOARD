#include<lpc21xx.h>
#include"delay.h"
#include"types.h"
#define CA7SEG 8
#define DSEL1 16
#define DSEL2	17
/*const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};*/
const u8 seglut[]={0xc0,0xf9,0x80};
void disp_2mux(u8 n);
s32 i,dly,j;
int main()
{
	IODIR0|=255<<CA7SEG;
	IODIR0|=1<<DSEL1|1<<DSEL2;
	for(i=0;i<3;i++)
	{
		for(j=0;j<5;j++)
		{
			disp_2mux(i);
			delay_ms(300);
		}
	}
	while(1);
}

void disp_2mux(u8 n)
{
     IOPIN0=(IOPIN0 & ~(255<<CA7SEG)) | (seglut[n%10]<<CA7SEG);

        IOSET0=1<<DSEL1;
        delay_ms(1);
        IOCLR0=1<<DSEL1;
  
	    IOPIN0=(IOPIN0 & ~(255<<CA7SEG)) | (seglut[n%10]<<CA7SEG);

        IOSET0=1<<DSEL2;
        delay_ms(1);
        IOCLR0=1<<DSEL2;
}
