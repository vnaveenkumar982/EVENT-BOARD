//settings.c
#include "settings.h"
#include "lcd_defines.h"
#include "lcd .h"
#include "delay.h"
#include "types.h"
#include "kpm_defines1.h"
#include <lpc21xx.h>
#include <stdlib.h>

u32 PSW=1;
s32 UserPSW;
u8 choice;
extern u32 msg_flag;


typedef struct 
{
	u8 hour;
	u8 minute;
	char text[80];
	u8 enabled; // 1 = show, 0 = skip (user controlled)
} Message;

extern Message messageList[10];
extern s8 hour,min,sec,dom,month,year,dow;

void settings()
{
	u8 flag=1;
	Cmdlcd(CLEAR_LCD);
	Strlcd("  ADMIN ");
	Cmdlcd(GOTO_LINE2_POS0);
	Strlcd("        MODE");
	delay_s(2);
b:Cmdlcd(CLEAR_LCD);
   Strlcd("ENTER PASSWORD");
	UserPSW = ReadNum2(10);
	
	if(UserPSW==-1)
	{
		Cmdlcd(CLEAR_LCD);
		  Strlcd("INVALID");
		  delay_s(2);
		 goto b;
	}
	
	if(UserPSW==PSW)
	{
		while(1)
		{
a:	Cmdlcd(CLEAR_LCD);
		Cmdlcd(GOTO_LINE1_POS0);
		Strlcd("1.Time 2.Date");
		Cmdlcd(GOTO_LINE2_POS0);
		Strlcd("3.day 4.Msg 5.Ex");
		choice = Keyscan();	
		switch(choice)
		{
				case '1':Edit_time();
								 break;
				case '2':Edit_date();
								 break;
				case '3':DOW = Edit_day();
								 break;
				case '4':MsgDisp();
								 break;
				case '5':flag=0;
								 break;
				default :Cmdlcd(CLEAR_LCD);
								 Strlcd("Invalid input");
								 delay_s(2);
								 goto a;
			}
		if(flag==0) break;
		}
	}
   else
   {
		  Cmdlcd(CLEAR_LCD);
		  Strlcd("INVALID PASSWORD");
		  delay_s(2);
		 goto b; 
   }
}
				
void Edit_time()
{
	while(1)
	{
			u8 ch,flag=1;
			Cmdlcd(CLEAR_LCD);
			Strlcd("1.Hr 2.Min 3.Sec");
			Cmdlcd(GOTO_LINE2_POS0);
			Strlcd("4.Back");
			ch=Keyscan();
				  switch(ch)
				  {
						case '1': HOUR = Edit_hour();
											break;
						case '2': MIN  = Edit_min();
											break;
						case '3': SEC  = Edit_sec();
											break;
						case '4': flag=0;break;
						default : Strlcd("  Invalid");
											delay_s(2);
				  }
				if(flag==0)
				{
					break;
				}
		}
}


s8 Edit_hour()
{
	s32 h;
	while(1)
	{
		Cmdlcd(CLEAR_LCD);
		Strlcd("ENTER HOUR(0-23)");
					Cmdlcd(GOTO_LINE2_POS0);
					h=ReadNum2(2);
					if(h==-1)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else if(h>23)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else 
					{
						return h;
					}
	}
}
s8 Edit_min()
{
	s32 m;
	while(1)
	{
				Cmdlcd(CLEAR_LCD);
				Strlcd("ENTER Mins(0-59)");
						Cmdlcd(GOTO_LINE2_POS0);
						m=ReadNum2(2);
						if(m == -1)
						{
							Strlcd(" Invalid");
							delay_s(2);
						}
						else if(m>59)
						{
							Strlcd(" Invalid");
							delay_s(2);
						}
						else
						{
							return m;
						}
		}
}
s8 Edit_sec()
{
	s32 s;
	while(1)
	{
				Cmdlcd(CLEAR_LCD);
				Strlcd("Enter secs(0-59)");
					Cmdlcd(GOTO_LINE2_POS0);
					s=ReadNum2(2);
					if(s==-1)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else if(s>59)
					{
						Strlcd("   Invalid");
						delay_s(1);
					}
					else
					{
						return s;
					}
	}
}


void Edit_date()
{
	s8 choice,flag=1;
	while(1)
	{
			Cmdlcd(CLEAR_LCD);
			Strlcd("1.Date 2.Month");
			Cmdlcd(GOTO_LINE2_POS0);
			Strlcd("3.Year 4.Back");
			choice=Keyscan();
				switch(choice)
				{
					case '1':DOM = Edit_Ndate();
									 break;
					case '2':MONTH = Edit_month();
							     break;
					case '3':YEAR = Edit_year();
										break;
					case '4': flag=0;break;
					default :Cmdlcd(CLEAR_LCD);
										Strlcd(" Invalid ");
									 delay_s(2);
				}
			if(flag==0)
				break;
		}
}
s8 Edit_Ndate()
{
	s32 d;
	while(1)
	{
				Cmdlcd(CLEAR_LCD);
				Strlcd("ENTER DATE(1-31)");
					d=ReadNum2(2);
					if(d==-1)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else if(d==0 || d>31)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else
					{
						return d;
					}
	}
}
s8 Edit_month()
{
	s32 m;
	while(1)
	{
				Cmdlcd(CLEAR_LCD);
				Strlcd("ENTER MONTH:1-12");
					m=ReadNum2(2);
					if(m == -1)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else if(m==0 || m>12)
					{
						Strlcd("   Invalid");
						delay_s(2);
					}
					else
					{
						return m;
					}
	}
}
s32 Edit_year()
{
	s32 y;
	while(1)
	{
					Cmdlcd(CLEAR_LCD);
					Strlcd("ENTER (2025-2999)");
					y=ReadNum2(4);
					if(y==-1)
					{
						Strlcd("  Invalid");
						delay_s(2);
					}
					else if(y<2025 || y>2999)
					{
						Strlcd("   Invalid");
						delay_s(2);
					}
					else
					{

						return y;
					}
		}
}
s8 Edit_day()
{
	s8 d;
	while(1)
	{
					Cmdlcd(CLEAR_LCD);
					Strlcd("0.Su 1.M 2.T 3.W");
					Cmdlcd(GOTO_LINE2_POS0);
					Strlcd("4.Th 5.Fr 6.Sa7E");
					d=Keyscan()-48;
					if(d>6)
					{
						Cmdlcd(CLEAR_LCD);
						Strlcd("Invalid");
						delay_s(2);
					}
					else
					{
						return d;
					}
	}
}

void MsgDisp()
{
	s32 ch,n;
	while(1)
	{
	u8 flag=1;
a:Cmdlcd(CLEAR_LCD);
	Strlcd("Enter Num:1-10");
	ch=ReadNum2(2);
	if(ch<=0 || ch>10)
	{
		Strlcd(" Invalid");
		delay_s(2);
		goto a;
	}
	//delay_ms(500);
	Cmdlcd(CLEAR_LCD);
	Strlcd("1.Enable 2.Disable");
	n=Keyscan();
				  switch(n)
				  {
						case '1': messageList[ch-1].enabled=1;
											msg_flag=1;
											flag=0;
											Cmdlcd(GOTO_LINE2_POS0);
											Strlcd("Enabled");
											delay_ms(500);
											break;
						case '2': messageList[ch-1].enabled=0;
											msg_flag=0;
											flag=0;
											Cmdlcd(GOTO_LINE2_POS0);
											Strlcd("Disabled");
											delay_ms(500);
											break;
						default : Strlcd("Invalid");
											delay_s(2);
				  }
					if(flag==0)
						break;
	}
}
/*
void MsgDisp()
{
	while(1)
	{
	u8 ch,flag=1;
	CmdLCD(CLEAR_LCD);
	StrLCD("Msg: 1.Ena 2.Dis");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3.Exit");
				  ch=Keyscan();
				  switch(ch)
				  {
						case '1': MsgEnable();
											flag=0;
											break;
						case '2': MsgDisable();
											flag=0;
											break;
						case '3': flag=0;break;
						default : StrLCD("Invalid");
											delay_s(2);
				  }
					if(flag==0)
						break;
	}
}
		
void MsgEnable()
{
	while(1)
	{
		s32 i;
		CmdLCD(CLEAR_LCD);
		StrLCD("Enter number:1-10");
		i=ReadNum2(2);
		if(i<0 || i>10)
		{
			StrLCD("Invalid");
			delay_s(2);
		}
		else
		{
			messageList[i-1].enabled=1;
			break;
		}
	}
}	

void MsgDisable()
{
	while(1)
	{
		s32 i;
		CmdLCD(CLEAR_LCD);
		StrLCD("Enter number:1-10");
		i=ReadNum2(2);
		if(i<0 || i>10)
		{
			StrLCD("Invalid");
			delay_s(2);
		}
		else
		{
			messageList[i-1].enabled=0;
			break;
		}
	}
}	
*/
		
