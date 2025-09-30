#include"lm35.h"
#include"types.h"
#include"lcd_defines.h"
#include"lcd .h"
#include"delay.h"
main()
{
	Initlcd();
	Strlcd("LM35 TEST");
	while(2)
	{
		Cmdlcd(GOTO_LINE2_POS0);
		U32lcd(Read_LM35());
		Strlcd("deg c");
	}
}
