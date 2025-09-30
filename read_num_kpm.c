#include "kpm.h"
#include "lcd .h"
#include "types.h"
#include "delay.h"

u32 read_num(void)
{
	u32 num=0,sum=0;
	while(1)
	{
		num=key_scan();
		delay_ms(100);
		while(colscan()==0);
		if((num>='0') && (num<='9'))
		{
			sum=(sum*10)+(num-'0');
			Charlcd(num);
			while(colscan()==0);
		}
		else
    {
       while(colscan()==0);
       break;
    }
	}
		return sum;
}

/*int main()
{
	u32 num;
	initkpm();
	Initlcd();
	while(1)
	{
		num=read_num();
		Cmdlcd(GOTO_LINE2_POS0+8);
		U32lcd(num);
	}
}
*/
