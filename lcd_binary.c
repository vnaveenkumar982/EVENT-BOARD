///////lcd_binary//////////
#include "lcd .h"
#include "lcd_defines.h"
#include "delay.h"

void Binlcd(u32 n, u8 nbd);

u32 ch;
s32 i;
int main()
{
	while(1)
	{
	Initlcd();
	for(ch=65;ch<=90;ch++)
	{
		Cmdlcd(CLEAR_LCD);
		Cmdlcd(GOTO_LINE1_POS0);
		Charlcd(ch);
		Cmdlcd(GOTO_LINE2_POS0);
		Binlcd(ch,8);
		delay_ms(50);
	}
	for(ch=97;ch<=122;ch++)
	{
		//Cmdlcd(CLEAR_LCD);
		Cmdlcd(GOTO_LINE1_POS0);
		Charlcd(ch);
		Cmdlcd(GOTO_LINE2_POS0);
		Binlcd(ch,8);
		delay_ms(50);
	}
	for(ch=48;ch<=57;ch++)
	{
		//Cmdlcd(CLEAR_LCD);
		Cmdlcd(GOTO_LINE1_POS0);
		Charlcd(ch);
		Cmdlcd(GOTO_LINE2_POS0);
		Binlcd(ch,8);
		delay_ms(500);
	}
}
}

void Binlcd(u32 n, u8 nbd)
{
	for(i=nbd;i>0;i--)
	{
		Charlcd(((n>>(i-1))&1)+48);
	}
}
