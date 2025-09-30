#include <LPC214X.H>


#include "lcd_defines.h"
#include "lcd .h"
#include "rtc_defines.h"

// Array to hold names of days of the week
u8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};


/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
  PREFRAC = PREFRAC_VAL;
	
  // Enable the RTC & select external clk source (for LPC2148)
	#ifndef _LPC2148_
		CCR = RTC_ENABLE;
	#else
		CCR = RTC_ENABLE | RTC_CLKSRC;
  #endif
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

/*
Display the RTC time on LCD
hour value (0–23)
minute value (0–59)
second value (0–59) seperated by ':'
*/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
	Cmdlcd(GOTO_LINE1_POS0);
	Charlcd((hour/10)+48);
	Charlcd((hour%10)+48);
	Charlcd(':');
	Charlcd((minute/10)+48);
	Charlcd((minute%10)+48);
	Charlcd(':');
	Charlcd((second/10)+48);
	Charlcd((second%10)+48);
}

/*
Get the current RTC date
day Pointer to store the current date (1–31)
month Pointer to store the current month (1–12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Day of month (1–31)
Month (1–12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
	Cmdlcd(GOTO_LINE2_POS0);
	Charlcd((date/10)+48);
	Charlcd((date%10)+48);
	Charlcd('/');
	Charlcd((month/10)+48);
	Charlcd((month%10)+48);
	Charlcd('/');
	U32lcd(year);
}

/*
Set the RTC time
Hour to set (0–23)
Minute to set (0–59)
Second to set (0–59)
*/
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;

}

/*
Set the RTC date
day of month to set (1–31)
month to set (1–12)
year to set (four digits)
*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *day)
{
	*day = DOW;
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u8 day)
{
	Cmdlcd(GOTO_LINE1_POS0+10);
	Strlcd((s8 *)week[day]);
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 day)
{
	DOW = day;
}
