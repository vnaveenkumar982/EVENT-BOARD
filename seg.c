#include<LPC21xx.h>
#include"types.h"
#include"defines7SEG.h"
#include"delay.h"
const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};

void init_7segs(void)
{
	IODIR0|=255<<CA7SEG_2_MUX_0_8;
	IODIR0|=1<<DSEL1|1<<DSEL2;
}
void disp_2_mux_segs(u8 n)
{
	IOPIN0=(IOPIN0&(~(255<<CA7SEG_2_MUX_0_8))) | ((seglut[n/10])<<CA7SEG_2_MUX_0_8);
	//turn on seg1
	IOSET0=1<<DSEL1;
	delay_ms(1);
	//turn off seg1
	IOCLR0=1<<DSEL1;
	
	IOPIN0=(IOPIN0&(~(255<<CA7SEG_2_MUX_0_8))) | ((seglut[n%10])<<CA7SEG_2_MUX_0_8);
	//turn on seg2
	IOSET0=1<<DSEL2;
	delay_ms(1);
	//turn off seg2
	IOCLR0=1<<DSEL2;
}
