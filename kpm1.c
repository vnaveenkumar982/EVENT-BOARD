//kpm.c

#include<lpc21xx.h>
#include "types.h"
#include "kpm_defines.h"
#include "defines.h"
#include "lcd_defines.h"
#include "lcd .h"
#include "delay.h"

u32 kpmLUT[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
void InitKPM(void)
{
        //cfg row as gpio out
        WRITENIBBLE(IODIR1,ROW0,15);
        //default,col lines are any input
}

u32 Colscan(void)
{
        u32 t;
        t=READNIBBLE(IOPIN1,COL0);
        return(t<15)?0:1;
}

u32 Rowcheck(void)
{
        u32 r;
        for(r=0;r<=3;r++)
        {
                //ground one row at a time
                WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
                //check if any key pressed in that row
                if(Colscan()==0)
                {
                        break;
                }
        }
        // re_initialize rows
        WRITENIBBLE(IOPIN1,ROW0,0);
        return r;
}

u32 Colcheck(void)
{
        u32 c;
        for(c=0;c<=3;c++)
        {
                if(READBIT(IOPIN1,COL0+c)==0)
                break;
        }
        return c;
}

u32 Keyscan(void)
{
        u32 r,c,keyv;
        while(Colscan());
        //if any key press detected
        //proceed to identify row in which key was pressed
        r=Rowcheck();
        //proceed to identify col in which key was presed
        c=Colcheck();
        //extract key value from look up table
        keyv=kpmLUT[r][c];
        while(Colscan()==0);
        return keyv;
}


u32 ReadPSW(void)
{
	u32 sum = 0;
	s8 key;
	u32 count = 0;
	while (1)
	{
		key = Keyscan();

		if ((key >= '0') && (key <= '9'))
		{
			sum = (sum * 10) + (key - '0');
			Cmdlcd(GOTO_LINE2_POS0 + count);
			Charlcd('*');
			count++;
			while (Colscan() == 0);
		}
		else if (key == '-')
		{
			if (count > 0)
			{
				sum = sum / 10;
				count--;
				Cmdlcd(GOTO_LINE2_POS0 + count);
				Charlcd(' ');
				Cmdlcd(GOTO_LINE2_POS0 + count);
			}
			while (Colscan() == 0);
		}
		else if (key == 'C')            // Clear/reset key
    {
         sum = 0;
         Cmdlcd(GOTO_LINE2_POS0);
         Strlcd("    ");     // Clear old display
				count=0;
		}
		else if (key == '=')
		{
			while (Colscan() == 0);
			break;
		}
	}

	return sum;
}

s32 ReadNum2(u32 n)
{
	u32 sum = 0;
	s8 key;
	u32 count = 0,char_cnt=0;
	while (1)
	{
		key = Keyscan();

		if ((key >= '0') && (key <= '9'))
		{
			if(n==10)
			{
			sum = (sum * 10) + (key - '0');
			Cmdlcd(GOTO_LINE2_POS0 + count);
			Charlcd('*');
			count++;
			}
			else //(n==2|n==10)
			{
				sum = (sum * 10) + (key - '0');
				Cmdlcd(GOTO_LINE2_POS0);
				U32lcd(sum);
				count++;
			}
			char_cnt++;
			if((n==10 || n==2 || n==4 ) && char_cnt>n)
			{
				return -1;
			}
			while (Colscan() == 0);
		}
	else	if (key == '-')
		{
			if (count > 0)
			{
				sum = sum / 10;
				count--;
				char_cnt--;
				Cmdlcd(GOTO_LINE2_POS0 + count);
				Charlcd(' ');
				Cmdlcd(GOTO_LINE2_POS0 + count);
			}
			while (Colscan() == 0);
		}
	else if (key == 'C')            // Clear/reset key
    {
         sum = 0;
         Cmdlcd(GOTO_LINE2_POS0);
         Strlcd("    ");     // Clear old display
				 count=0;
				 char_cnt=0;
		}
		else if (key == '=' && count>0)
		{
			while (Colscan() == 0);
			break;
		}
	}

	return sum;
}
