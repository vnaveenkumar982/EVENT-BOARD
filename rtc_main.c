#include <lpc21xx.h>

//include required header files
#include "types.h"
#include "lcd .h"
#include "lcd_defines.h"
#include "delay.h"
#include "rtc.h"


s32 hour,min,sec,date,month,year,day;

// Main function
int main()
{
  // Initialize RTC 
	RTC_Init();
		
  // Initialize the LCD
	Initlcd();
	Strlcd("rtc info");
	delay_s(1);
	Cmdlcd(CLEAR_LCD);
	
  // Set the initial time (hours, minutes, seconds)
	SetRTCTimeInfo(15,35,00);
	SetRTCDateInfo(15,7,2025);
	SetRTCDay(2);

    while (1) 
		{
      // Get and display the current time on LCD
			GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
			GetRTCDateInfo(&date,&month,&year);
			DisplayRTCDate(date,month,year);
			GetRTCDay(&day);
			DisplayRTCDay(day);
    }
}
