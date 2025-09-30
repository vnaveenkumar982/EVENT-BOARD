#include "lcd .h"
#include <string.h>
#include "lcd_defines.h"
#include "delay.h"

int main(void)
{
    u8 msg[] = "  EMBEDDED SYSTEMS  "; // Extra spaces for smooth scroll
    int len = strlen((char *)msg);     // cast to match strlen's expected type
    int i, j;

    Initlcd();

    while(1)
    {
        for(i = 0; i < len - 15; i++) // show only 16 chars at a time
        {
            Cmdlcd(0x80); // set cursor to first line start
            for(j = 0; j < 16; j++)
            {
                Charlcd(msg[i + j]); // send one character
            }
            delay_ms(300); // scroll speed
        }
    }
}
