#include"lcd_defines.h"
#include"delay.h"
#include"lcd .h"

s8 msg[40]="Good Morning! Classes Start Soon";
s8 msg1[45]="C Programming Session in Class room number 2";
s8 msg2[40] = "C module theory exam in 4th floor lab1";
s8 msg3[62] = "C module lab exam in 4th floor lab2 and middle lab at 10:30AM";
s8 msg4[40] = "Lunch Break from 1PM – 2PM";
s8 msg5[52] = "ARM Workshop on external interrupts in LAB1 at 10AM";
s8 msg6[53] = "ARM kit issue time from 10AM – 10:30AM in middle lab";
s8 msg7[45] = "Only 15 mins break time for next ARM session";
s8 msg8[40] = "Revise today’s Class programs at home!";
s8 msg9[40] = "End of Day – See You Tomorrow!";

void scroll_msg(s8 *msg,u8 msg_len,u32 timems);
int main()
{
	Initlcd();
	while(1)
	{
		Cmdlcd(GOTO_LINE2_POS0);
		Strlcd("  EVENT BOARD  ");
		Cmdlcd(GOTO_LINE1_POS0);
		scroll_msg(msg,40,50);
		delay_ms(50);
		scroll_msg(msg1,45,50);
		delay_ms(50);
		scroll_msg(msg2,40,50);
		delay_ms(50);
		scroll_msg(msg3,62,50);
		delay_ms(50);
		scroll_msg(msg4,40,50);
		delay_ms(50);
		scroll_msg(msg5,52,50);
		delay_ms(50);
		scroll_msg(msg6,53,50);
		delay_ms(50);
		scroll_msg(msg7,45,50);
		delay_ms(50);
		scroll_msg(msg8,40,50);
		delay_ms(50);
		scroll_msg(msg9,40,50);
		delay_ms(50);	
	}
}

void scroll_msg(s8 *msg,u8 msg_len,u32 timems)
{
	s8 arr[17];
	s32 i,j,pos;
	for(i=0;i<(msg_len)+16;i++)
	{
		for(j=0;j<=16;j++)
		{
				pos=i-16+j;
				if(pos>=0 && pos<msg_len)
					arr[j]=msg[pos];
				else
					arr[j]=' ';
		}
		arr[16]='\0';
		Cmdlcd(GOTO_LINE1_POS0);
		for(j=0;j<=16;j++)  
		{
			Charlcd(arr[j]);
		}
		delay_ms(timems);
	}
}



