#include<LPC21xx.h>
#include"types.h"
#include"defines7SEG.h"
#include"delay.h"
#include"defines.h"
#define DSEL1 16
const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};

void init_7segs(void)
{
	IODIR0|=255<<CA7SEG_4_MUX_0_8;
	//IODIR0|=1<<DSEL1|1<<DSEL2|1<<DSEL3|1<<DSEL4;
	WRITENIBBLE(IODIR0,DSEL1,15);
}
void disp_2_mux_segs(u8 n,u8 segnostart)
{
	IOPIN0=(IOPIN0&(~(255<<CA7SEG_4_MUX_0_8 ))) | (seglut[n/10])<<CA7SEG_4_MUX_0_8;
	
	IOSET0=1<<(DSEL1+segnostart);
	delay_ms(1);
	IOCLR0=1<<(DSEL1+segnostart);
	if(segnostart==0)
	{
		IOPIN0=(IOPIN0&(~(255<<CA7SEG_4_MUX_0_8 ))) | ((seglut[n%10])&0x7f)<<CA7SEG_4_MUX_0_8;
	}
	else if(segnostart==2)
	{
		IOPIN0=(IOPIN0&(~(255<<CA7SEG_4_MUX_0_8 ))) | (seglut[n%10])<<CA7SEG_4_MUX_0_8;
	}
	IOSET0=1<<(DSEL1+segnostart+1);
	delay_ms(1);
	IOCLR0=1<<(DSEL1+segnostart+1);

}
