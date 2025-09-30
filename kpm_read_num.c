#include"types.h"
#include"lcd .h"
#include"lcd_defines.h"
#include"KPM_DEFINES.H"
#include"kpm.h"
u32 readnum(void)
{
        u32 sum=0,num=0;
        while(1)
        {
                num=key_scan();
                Cmdlcd(GOTO_LINE2_POS0+8);
                U32lcd(num);
                if((num >0) && (num <=9))
                {
                        sum=(sum*10)+(num);
                        Cmdlcd(GOTO_LINE2_POS0);
                        U32lcd(sum);
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
int main()
{
        u32 num;
        Initlcd();
        initkpm();
        Strlcd("4X4 KPM TEST");
        while(1)
        {
                num=readnum();
                //cmdlcd(GOTO_LINE2_POS0+8);
                U32lcd(num);
        }
}


