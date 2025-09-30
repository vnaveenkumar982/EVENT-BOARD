/*#include <lpc21xx.h>
#include "lcd .h"
#include "kpm.h"
#include "delay.h"
#include "types.h"
#include "lcd_defines.h"

#define LED 8

u32 read_num(void);
u32 num;
int i;

int main()
{
    Initlcd();
    initkpm();

    IODIR0 |= 255 << LED;
    IOSET0 = 255 << LED;

    while (1)
    {
        num = read_num();  // Read decimal number from keypad

        Cmdlcd(CLEAR_LCD);
        Strlcd("Binary:");
        Cmdlcd(GOTO_LINE2_POS0);

        for (i = 7; i >= 0; i--)
        {
            if (num & (1 << i))
                Charlcd('1');
            else
                Charlcd('0');
        }
        delay_ms(2000);
    }
}
*/

#include<lpc21xx.h>
#include "lcd .h"
#include "types.h"
#include "lcd_defines.h"
#include "kpm.h"

u8 checkprime(int num);
u32 key_scan(void);
u32 readnum(void);

u32  n,i,k;
int main()
{
        Initlcd();
        initkpm();
        while(1)
        {
        n=readnum();
        Cmdlcd(GOTO_LINE1_POS0);
        U32lcd(n);
        k=checkprime(n);
        if(k==1)
        {
                Cmdlcd(GOTO_LINE2_POS0);
                Strlcd("It is prime");
        }
        else
        {
                Cmdlcd(GOTO_LINE2_POS0);
                Strlcd("           ");
                Cmdlcd(GOTO_LINE2_POS0);
                Strlcd("Not prime");
        }
        }
}

u8 checkprime(int num)
{
        for(i=2;i<num;i++)
        {
                 if(num%i==0)
                 {
                        return 0;
                 }
        }
        return 1;
}

u32 readnum(void)
{
        u32 sum = 0, num = 0;
        while(1)
        {
                num = key_scan();

                if((num >= '0') && (num <= '9'))
                {
                        sum = (sum * 10) + (num - '0');
                        Cmdlcd(GOTO_LINE2_POS0);
                        Cmdlcd(CLEAR_LCD);
                        U32lcd(sum);

                        while(colscan() == 0);
                }
                else
                {
                        while(colscan() == 0);
                        break;
                }
        }
        return sum;
}

