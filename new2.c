#include "lcd .h"
#include <LPC21xx.h>
#include "lcd_defines.h"
#include "delay.h"
#include <string.h>
#include "types.h"
#include "rtc_defines.h"
#include "rtc.h"
#include "adc.h"
#include "adc_defines.h"
#include "lm35.h" 

#define TOTAL_MSG 10

void eint0_enable(void);
volatile u8 admin_flag = 0;
void admin_mode(void);
u32 readnum(void);

// Message structure
typedef struct {
    u32 hour;
    u32 min;
    char text[80];
    u8 enabled;
} MSG;

// Predefined messages
MSG messageList[TOTAL_MSG] = {
    {7, 45, "                Good Morning! Classes Start Soon      ", 1},
    {7, 47, "       				 C Programming Session in Class room number 2     ", 1},
    {10, 15, "               C module theory exam in 4th floor lab1   ", 1},
    {10, 15, "               C module lab exam in 4th floor lab2 and middle lab at 10:30AM    ", 1},
    {12, 45, "               Lunch Break from 1PM – 2PM      ", 1},
    {9, 45, "                ARM Workshop on external interrupts in LAB1 at 10AM    ", 1},
    {9, 45, "                ARM kit issue time from 10AM – 10:30AM in middle lab    ", 1},
    {15, 15, "               Only 15 mins break time for next ARM session      ", 1},
    {17, 00, "               Revise today’s Class programs at home!       ", 1},
    {17, 45, "               End of Day – See You Tomorrow!         ", 1}
};

// Function to scroll message
void msg_scroll(char *p, u32 size, char dir, u32 timeMS)
{
    char scroll[160];
    char shiftdata[17];
    int i, j, len;

    strncpy(scroll, p, size);
    scroll[size] = '\0';
    strcat(scroll, "                ");
    len = strlen(scroll);

    for (i = 0; i < len - 15; i++)
    {
        for (j = 0; j < 16; j++)
        {
            shiftdata[j] = scroll[i + j];
        }
        shiftdata[16] = '\0';

        Cmdlcd(GOTO_LINE1_POS0);
        Strlcd(shiftdata);
        delay_ms(timeMS);
    }
}

int main()
{
    u32 i;
    s32 hour, min, sec;
    s32 date, month, year, day;
    u32 temp;

    RTC_Init();     // Initialize RTC
    Initlcd();      // LCD
    initkpm();      // Keypad
    eint0_enable(); // External interrupt

    // LEDs
    IODIR1 |= 1 << 27; // RED
    IODIR1 |= 1 << 28; // GREEN
    IOSET1 = (1 << 27) | (1 << 28); // Both ON for testing

    // Set initial RTC values (demo)
    SetRTCTimeInfo(7, 44, 59);
    SetRTCDateInfo(22, 7, 2025);
    SetRTCDay(2); // Tuesday

    while (1)
    {
        if (admin_flag)
        {
            admin_mode();
            admin_flag = 0;
            Cmdlcd(0x01); // Clear LCD
            delay_ms(500);
        }

        // Turn ON GREEN (idle), OFF RED
        IOSET1 = 1 << 28;
        IOCLR1 = 1 << 27;

        // Get current time and date
        GetRTCTimeInfo(&hour, &min, &sec);
        GetRTCDateInfo(&date, &month, &year);
        GetRTCDay(&day);

        // Display time/date/day
        DisplayRTCTime(hour, min, sec);
        DisplayRTCDate(date, month, year);
        Strlcd("     ");
        DisplayRTCDay(day);

        // Show temperature
        temp = Read_LM35();
        Cmdlcd(GOTO_LINE2_POS0 + 11);
        U32lcd(temp);
        Strlcd("C");

        // Check message match
        for (i = 0; i < TOTAL_MSG; i++)
        {
            if (messageList[i].enabled == 1 &&
                messageList[i].hour == hour &&
                messageList[i].min == min)
            {
                // Turn ON RED, OFF GREEN
                IOSET1 = 1 << 27;
                IOCLR1 = 1 << 28;

                // Show label
                Cmdlcd(GOTO_LINE2_POS0);
                Strlcd("   EVENT BOARD  ");

                // Scroll message once
                msg_scroll(messageList[i].text, strlen(messageList[i].text), 'l', 50);

                break; // Exit after one match
            }
        }

        //delay_ms(1000); // 1 sec delay before next loop
    }
}


/*void msg_scroll(char *p, u32 size, char dir, u32 timeMS)
{
    char scroll[160];
    char shiftdata[17];
    int i, j, len;

    // Prepare scrolling buffer
    strncpy(scroll, p, size);
    scroll[size] = '\0';
    strcat(scroll, "                "); // padding for wrap
    len = strlen(scroll);

    // Scroll through the message once
    for (i = 0; i < len - 15; i++)
    {
        for (j = 0; j < 16; j++)
        {
            shiftdata[j] = scroll[i + j];
        }
        shiftdata[16] = '\0';

        Cmdlcd(GOTO_LINE1_POS0);
        Strlcd(shiftdata);
        delay_ms(timeMS);  // Set small delay for fast scroll
    }
}
*/