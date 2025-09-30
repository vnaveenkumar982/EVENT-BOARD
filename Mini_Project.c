////Main.c////////////
#include <LPC21xx.h>
#include "lcd .h"
#include "delay.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "adc.h"
#include "lm35.h"
#include "kpm.h"
#include "types.h"
#include "eint.h"
#include "lcd_defines.h"

#define TOTAL_MSG 10
#define LED_RED 27
#define LED_GREEN 30

u8 admin_flag = 0;
void admin_mode(void);
void eint0_enable(void); 


typedef struct 
{
    u32 hour;
    u32 min;
    char text[80];
    u8 enabled;
}MSG;

MSG messageList[TOTAL_MSG] = {
{7, 45, "                Good Morning! Classes Start Soon      ", 0},
{7, 47, "       				 C Programming Session in Class room number 2     ", 0},
{10, 15, "               C module theory exam in 4th floor lab1   ", 0},
{10, 15, "               C module lab exam in 4th floor lab2 and middle lab at 10:30AM    ", 0},
{12, 45, "               Lunch Break from 1PM – 2PM      ", 0},
{9, 45, "                ARM Workshop on external interrupts in LAB1 at 10AM    ", 0},
{9, 45, "                ARM kit issue time from 10AM – 10:30AM in middle lab    ", 0},
{15, 15, "               Only 15 mins break time for next ARM session      ", 0},
{17, 00, "               Revise today’s Class programs at home!       ", 0},
{17, 45, "               End of Day – See You Tomorrow!         ", 0}
};

void msg_scroll(char *p, u32 size, char dir, u32 timeMS);

int main(void) {
    u32 i, j, len = 80;
    s32 hour, min, sec;
    s32 date, month, year, day;
    u32 startMin, startHour;
		
    
    IODIR1 |= (1 << LED_RED) | (1 << LED_GREEN);
    Initlcd();
    initkpm();
    RTC_Init();
    eint0_enable();  // External interrupt setup

    SetRTCTimeInfo(7, 44, 59);
    SetRTCDateInfo(22, 7, 2025);
    SetRTCDay(2);

    while (1) 
		{
        if (admin_flag) 
				{
            admin_flag = 0;
            Cmdlcd(CLEAR_LCD);
						admin_mode(); 
            delay_ms(100);
            Cmdlcd(CLEAR_LCD);
        }
				IOSET1 = 1 << LED_GREEN;
        IOCLR1 = 1 << LED_RED;
  
        GetRTCTimeInfo(&hour, &min, &sec);
        DisplayRTCTime(hour, min, sec);

        GetRTCDateInfo(&date, &month, &year);
        DisplayRTCDate(date, month, year);

        GetRTCDay(&day);
        DisplayRTCDay(day);
				
        Cmdlcd(GOTO_LINE2_POS0 + 12);
        U32lcd(Read_LM35());
        Charlcd('C');

        for (i = 0; i < TOTAL_MSG; i++) 
				{
            if (messageList[i].enabled == 1 &&
                messageList[i].hour == hour &&
                messageList[i].min == min) 
						{
                Cmdlcd(GOTO_LINE2_POS0);
                Strlcd("   EVENT BOARD  ");

                startHour = hour;
                startMin = min;

                while (1) 
								{
										IOSET1 = 1 << LED_RED;
										IOCLR1 = 1 << LED_GREEN;
                    GetRTCTimeInfo(&hour, &min, &sec);

                    // Exit scrolling after 1 minute
                    if ((hour * 60 + min) - (startHour * 60 + startMin) > 0 || admin_flag) 
										{
                        Cmdlcd(CLEAR_LCD);
                        break;
                    }

                    for (j = 0; j < len; j++) 
										{
                        if (admin_flag) 
												{
                            Cmdlcd(CLEAR_LCD);
                            break;
                        }
                        Cmdlcd(GOTO_LINE1_POS0);
                        Strlcd(messageList[i].text);
                        msg_scroll(messageList[i].text, len, 'l', 10);
                    }
                }
            }
        }
    }
}

// Scroll function
void msg_scroll(char *p, u32 size, char dir, u32 timeMS) {
    char temp;
    s32 i;

    if (dir == 'l') {
        temp = p[0];
        for (i = 0; i < size - 1; i++)
        p[i] = p[i + 1];
        p[i] = temp;
    }
    delay_ms(timeMS);
}
