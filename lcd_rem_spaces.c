#include <lpc21xx.h>
#include "types.h"
#include "lcd_defines.h"
#include "delay.h"
#include "lcd .h"
#include <string.h>

#define SW1 1   // P0.1
#define SW2 2   // P0.2

void remove_extra_spaces(char *str);

char str1[32] = " An  Apple a day";
char str2[32] = " vector   stu  !";
char temp[32];

int main() {
    Initlcd();

    while (1) {
        if (((IOPIN0 >> SW1) & 1) == 0) {
            Cmdlcd(CLEAR_LCD);
            strcpy(temp, str1);
            Cmdlcd(GOTO_LINE1_POS0);
            Strlcd(temp);

            while (((IOPIN0 >> SW1) & 1) == 0);

            remove_extra_spaces(temp);
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd(temp);
            delay_ms(2000);
        }
        else if (((IOPIN0 >> SW2) & 1) == 0) {
            Cmdlcd(CLEAR_LCD);
            strcpy(temp, str2);
            Cmdlcd(GOTO_LINE1_POS0);
            Strlcd(temp);

            while (((IOPIN0 >> SW2) & 1) == 0);

            remove_extra_spaces(temp);
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd(temp);
            delay_ms(2000);
        }
				
        else {
            Cmdlcd(GOTO_LINE1_POS0);
            Strlcd("waiting for input");
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("                ");
        }
    }
}

void remove_extra_spaces(char *str) {
    int i = 0, j = 0;
    int space_flag = 0;

    while (str[i] != '\0')
		{
        if (str[i] != ' ') 
					{
            str[j++] = str[i];
            space_flag = 0;
					} 
					else 
					{
            if(space_flag == 0) 
						{
                str[j++] = str[i];
                space_flag = 1;
						}
					}
        i++;
			}
    str[j] = '\0';
}
