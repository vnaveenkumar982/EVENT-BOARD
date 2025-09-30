#include<lpc21xx.h>
#include"types.h"
#include"lcd .h"
#include"lcd_defines.h"
int main()
{
	u32 hour=12,min=40,sec=30;
	Initlcd();
	while(1)
	{
		Cmdlcd(GOTO_LINE1_POS0);
		Charlcd((hour/10)+48);
		Charlcd((hour%10)+48);
		Charlcd(':');
		Charlcd((min/10)+48);
		Charlcd((min%10)+48);
		Charlcd(':');
		Charlcd((sec/10)+48);
		Charlcd((sec%10)+48);
	}
}

