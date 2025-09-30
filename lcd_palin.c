/////lcd_palin_asg.c/////

#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd .h"
#include "delay.h"
#include "types.h"
#include <stdlib.h>

s32 i;
u32 arr[10],seed=1;

int check_palin(int n);

int main()
{
	while(1)
	{
		Initlcd();
		Cmdlcd(GOTO_LINE1_POS0);
		Strlcd("Palindrome");
		for(i=0;i<10;i++)
		{
			arr[i]=rand()%800+100;
			srand(seed++);
		}
		for(i=0;i<10;i++)
		{
			if(check_palin(arr[i]))
			{
				Cmdlcd(GOTO_LINE2_POS0);
				U32lcd(arr[i]);
				delay_ms(500);
				
			}
		}
	}
}
int check_palin(int n)
{
	u32 digit=0,rev=0;
	u32 temp=n;
	while(temp>0)
	{
			digit=temp%10;
			rev=rev*10+digit;
			temp/=10;
	}
	return (rev==n);
}

/*
#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd .h"
#include "delay.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

char s[100] = {"madam"};

int main()
{
    char *left;
    char *right;

    Initlcd();

    left = s;
    right = (s + strlen(s) - 1);
		Cmdlcd(GOTO_LINE1_POS0);
		Strlcd("String");
    while (left < right)
    {
        if (*left != *right)
        {
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("Not a palindrome");
            return 0;
        }
        left++;
        right--;
    }

    Cmdlcd(GOTO_LINE2_POS0);
    Strlcd("It is a palindrome");

    while(1);  // keep displaying
}

*/

