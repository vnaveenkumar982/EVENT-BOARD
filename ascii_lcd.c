
#include <lpc21xx.h>
#include "types.h"
#include "lcd_defines.h"
#include "delay.h"
#include "lcd .h"

void ascii_block(u8 c1, u8 c2, u8 c3, u8 c4);
u8 ch;
int main()
{
    Initlcd();

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        ascii_block(ch, ch + 3, ch + 7, ch + 14);
        delay_ms(500);
    }

    for (ch = 'a'; ch <= 'z'; ch++)
    {
        ascii_block(ch, ch + 3, ch + 7, ch + 14);
        delay_ms(500);
    }

    for (ch = '0'; ch <= '9'; ch++)
    {
        ascii_block(ch, ch + 1, ch + 2, ch + 3);
        delay_ms(500);
    }
    while (1);
}

void ascii_block(u8 c1, u8 c2, u8 c3, u8 c4)
{
    Cmdlcd(CLEAR_LCD);
    Cmdlcd(GOTO_LINE1_POS0);
    Charlcd(c1);
    Cmdlcd(GOTO_LINE1_POS0+4);
    Charlcd(c2);
    Cmdlcd(GOTO_LINE1_POS0+8);
    Charlcd(c3);
    Cmdlcd(GOTO_LINE1_POS0+12);
    Charlcd(c4);

    Cmdlcd(GOTO_LINE2_POS0);
    U32lcd(c1);
    Cmdlcd(GOTO_LINE2_POS0+4);
    U32lcd(c2);
    Cmdlcd(GOTO_LINE2_POS0+8);
    U32lcd(c3);
    Cmdlcd(GOTO_LINE2_POS0+12);
    U32lcd(c4);
}
