//lcdtest.c
#include"lcd_defines.h"
#include"delay.h"
#include"lcd .h"
s8 msg[]="Naveen kumar vemula";
s32 i;
int main()
{
	while(1)
	{
		Initlcd();
		Cmdlcd(GOTO_LINE1_POS0);
		Charlcd('a');
		Strlcd(" Naveen Kumar");
		Cmdlcd(GOTO_LINE2_POS0);
		U32lcd(1234567890);
		delay_s(1);
	}
}


