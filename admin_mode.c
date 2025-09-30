///Admin mode////////
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct
{
    u32 hour;
    u32 min;
    char text[80];
    u8 enabled;
} MSG;

extern MSG messageList[10];

#include <LPC21xx.h>
#include "lcd .h"
#include "delay.h"
#include "rtc.h"
#include "kpm.h"
#include "types.h"
#include "lcd_defines.h"

void admin_mode(void);
u32 readnum(void);
void msg_enable(void);
void msg_disable(void);
u32 readpass(void);

u32 pass;
u8 option;
s32 hour, min, sec, date, month, year;
// ****************** ADMIN MODE **********************
void admin_mode()
{
    // Get current RTC values
    GetRTCTimeInfo(&hour, &min, &sec);
    GetRTCDateInfo(&date, &month, &year);

    Cmdlcd(0x01);    
    Cmdlcd(0x80);
    Strlcd("Enter Password:");
    pass = readpass();  // Read 4-digit password from keypad

    if (pass == 1234)
    {
        Cmdlcd(GOTO_LINE2_POS0 + 5);
        Strlcd("Success");
        delay_ms(100);

        while (1)
        {
            Cmdlcd(CLEAR_LCD);
            Cmdlcd(GOTO_LINE1_POS0);
						Strlcd("1:H 2:M 3:S 4:D 5:M");
            Cmdlcd(GOTO_LINE2_POS0 );
						Strlcd("6:Y 7:E 8:D 9:Ex");
					
            delay_ms(100);
            option = key_scan();
            while (colscan() == 0); // Wait for release
            Cmdlcd(CLEAR_LCD);

            switch (option)
            {
                case '1':
                    Strlcd("Set Hour:");
                    hour = readnum();
                    break;
                case '2':
                    Strlcd("Set Min:");
                    min = readnum();
                    break;
                case '3':
                    Strlcd("Set Sec:");
                    sec = readnum();
                    break;
                case '4':
                    Strlcd("Set Date:");
                    date = readnum();
                    break;
                case '5':
                    Strlcd("Set Month:");
                    month = readnum();
                    break;
                case '6':
                    Strlcd("Set Year:");
                    year = readnum();
                    break;
                case '7':
                    msg_enable();   // Call enable function
                    break;
                case '8':
                    msg_disable();  // Call disable function
                    break;
                case '9':
                    Cmdlcd(CLEAR_LCD);
                    Strlcd("Exiting Admin...");
                    delay_ms(100);
                    return;
                default:
                    Strlcd("Invalid Option");
                    delay_ms(100);
                    break;
            }

            // Apply new RTC values
            SetRTCTimeInfo(hour, min, sec);
            SetRTCDateInfo(date, month, year);
        }
    }
    else
    {
        Strlcd("Wrong Password");
        delay_ms(100);
    }
}

//***************** MSG ENABLE *******************
void msg_enable(void)
{
    u32 ch2;
    while (1)
    {
        Cmdlcd(CLEAR_LCD);
        Strlcd("Enable Msg (1-10):");
        ch2 = readnum();

        if (ch2 <= 0 || ch2 > 10)
        {
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("Invalid Msg No");
            delay_ms(100);
        }
        else
        {
            messageList[ch2 - 1].enabled = 1;
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("Enabled Msg ");
            Charlcd(ch2 + '0');
            delay_ms(100);
            break;
        }
    }
}

// *************** MSG DISABLE ****************
void msg_disable(void)
{
    u32 ch2;
    while (1)
    {
        Cmdlcd(CLEAR_LCD);
        Strlcd("Disable Msg (1-10):");
        ch2 = readnum();

        if (ch2 <= 0 || ch2 > 10)
        {
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("Invalid Msg No");
            delay_ms(100);
        }
        else
        {
            messageList[ch2 - 1].enabled = 0;
            Cmdlcd(GOTO_LINE2_POS0);
            Strlcd("Disabled Msg ");
            Charlcd(ch2 + '0');
            delay_ms(100);
            break;
        }
    }
}

// ***************** READ NUM *******************
u32 readnum(void)
{
    u32 sum = 0;
    u8 key;
    u8 count = 0;

    Cmdlcd(GOTO_LINE2_POS0);  // Move to 2nd line

    while (1)
    {
        key = key_scan();

        if (key >= '0' && key <= '9')
        {
            sum = sum * 10 + (key - '0');
            Charlcd(key);
            count++;
            while (colscan() == 0);
        }
        else if(key == '*')  // Backspace
        {
            if (count > 0)
            {
                count--;
                Cmdlcd(0x10);
                Charlcd(' ');
                Cmdlcd(0x10);
            }
            while(colscan() == 0);
        }
        else
        {
            while(colscan() == 0);
            break;
        }

        if(count >= 4)
            break;
    }

    return sum;
}

// **************** READ PASSWORD ****************
u32 readpass(void)
{
    u32 sum = 0;
    u8 key;
    u8 count = 0;

    Cmdlcd(GOTO_LINE2_POS0);  

    while (1)
    {
        key = key_scan();

        if (key >= '0' && key <= '9')
        {
            sum = sum * 10 + (key - '0');
            Charlcd('*');  
            count++;
            while(colscan() == 0);
        }
        else if(key == 'B')  // Backspace
        {
            if (count > 0)
            {
                count--;
                sum /= 10;
                Cmdlcd(SHIFT_DSP_LEFT);
                Charlcd(' ');
                Cmdlcd(SHIFT_DSP_LEFT);
            }
            while(colscan() == 0);
        }
        else 
        {
            while(colscan() == 0);
            break;
        }

        if (count >= 4)   // 4-digit password max
            break;
    }

    return sum;
}
