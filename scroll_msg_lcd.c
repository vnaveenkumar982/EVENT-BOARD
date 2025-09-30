#include"types.h"
#include"delay.h"
#include<lpc21xx.h>
#include"lcd .h"
#include"lcd_defines.h"
s8 msg[17]="Institute        ";
void msg_scroll(s8 *p,u8 size,s8 dir,u32 timems);
int main()
{
				Initlcd();
        while(1)
        {
								Cmdlcd(GOTO_LINE1_POS0);
								Strlcd("     VECTOR");
								Cmdlcd(GOTO_LINE2_POS0);
								Strlcd(msg);
                msg_scroll(msg,17,'l',100);
        }
}
void msg_scroll(s8 *p,u8 size,s8 dir,u32 timems)
{
        s8 temp;
        s32 i;
        if(dir=='l')
        {
                temp=p[0];
                for(i=0;i<(size)-1;i++)
                {
                        p[i]=p[i+1];
                }
                p[i]=temp;
        }
        else if(dir=='r')
        {
                temp=p[size-2];
                for(i=(size-2);i>0;i--)
                {
                        p[i]=p[i-1];
                }
                p[i]=temp;
        }
        delay_ms(100);
}


