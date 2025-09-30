
#include"lcd .h"
#include"lcd_defines.h"
#include"types.h"
#include"delay.h"
#include<lpc21xx.h>
#include<string.h>
#include<stdlib.h>

#define SW1 1
#define SW2 2
void is_capitalise(char *ptr);
u32 len,i;
char str[20]="vector india";
char str1[20]="vector hyderabad";
char original[20];
int main()
{
Initlcd();
//len=strlen(str);
while(1)
{
if(((IOPIN0 >> SW1) & 1) == 0)
{
        Cmdlcd(CLEAR_LCD);
        strcpy(original,str);
        Cmdlcd(GOTO_LINE1_POS0);
        Strlcd(original);
        while (((IOPIN0 >> SW1) & 1) == 0);
        is_capitalise(str);
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd(str);
        is_capitalise(str);
        delay_ms(1000);
}
else if(((IOPIN0 >> SW2) & 1) == 0)
{
        Cmdlcd(CLEAR_LCD);
        strcpy(original,str1);
        Cmdlcd(GOTO_LINE1_POS0);
        Strlcd(original);
        while (((IOPIN0 >> SW2) & 1) == 0);
        is_capitalise(str1);
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd(str1);
        is_capitalise(str1);
        delay_ms(1000);
}
else
{
        Cmdlcd(GOTO_LINE1_POS0);
        Strlcd("Waiting input    ");
        Cmdlcd(GOTO_LINE2_POS0);
        Strlcd("                  ");
}
}
}

void is_capitalise(char *ptr)
{
u32 i,cnt=0,len;
len=strlen(ptr)-1;
for(i=0;i<=len;i++)
{
        cnt++;
        if(cnt==1)
        {
                ptr[i]^=32;
        }
        else if(cnt>len)
        {
                ptr[i]^=32;
        }
}
}
