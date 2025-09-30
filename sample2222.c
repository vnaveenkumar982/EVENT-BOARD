#include <lpc21xx.h>
#include "lcd_defines.h"
#include "lcd .h"
#include "kpm.h"
#include "rtc.h"
#include "delay.h"

#define EINT0_CH_NO 14
#define LED 8
u32 readnum(void);
volatile u8 update_rtc = 0;

// --- Interrupt Service Routine ---
void eint0_isr(void) __irq
{
    update_rtc = 1;         // Just raise a flag
    EXTINT = 1 << 0;        // Clear EINT0 flag
    VICVectAddr = 0;        // End of ISR
}

// --- Configure EINT0 on P0.14 ---
void eint0_enable(void)
{
    IODIR0 |= 1 << LED;            // LED output (optional)
    PINSEL0 |= 0x0000000C;          // Set P0.1 as EINT0
    VICIntSelect &= ~(1 << EINT0_CH_NO);   // EINT0 as IRQ
    VICIntEnable |= (1 << EINT0_CH_NO);    // Enable EINT0
    VICVectCntl0 = (1 << 5) | EINT0_CH_NO; // Slot 0
    VICVectAddr0 = (unsigned)eint0_isr;    // ISR address
    EXTINT = 1 << 0;              // Clear pending EINT0
    EXTMODE |= 1 << 0;            // Edge-sensitive
    EXTPOLAR &= ~(1 << 0);        // Falling edge
}

// --- Menu to Modify RTC Time/Date ---
void ShowRTCTimeUpdateMenu(void)
{
    u32 choice = 0, value = 0;
    s32 h, m, s, d, mo, y;

    Cmdlcd(0x01);
    Strlcd("1:Hr 2:Min 3:Sec");
    Cmdlcd(GOTO_LINE2_POS0);
    Strlcd("4:Dt 5:Mo 6:Yr");
    delay_ms(2000);

    Cmdlcd(CLEAR_LCD);
    Strlcd("Enter Opt:");
    choice = readnum();
	
    Cmdlcd(CLEAR_LCD);
    Strlcd("Enter Value:");
    value = readnum();

    switch (choice)
    {
        case 1:
            GetRTCTimeInfo(&h, &m, &s);
            SetRTCTimeInfo(value, m, s);
            break;
        case 2:
            GetRTCTimeInfo(&h, &m, &s);
            SetRTCTimeInfo(h, value, s);
            break;
        case 3:
            GetRTCTimeInfo(&h, &m, &s);
            SetRTCTimeInfo(h, m, value);
            break;
        case 4:
            GetRTCDateInfo(&d, &mo, &y);
            SetRTCDateInfo(value, mo, y);
            break;
        case 5:
            GetRTCDateInfo(&d, &mo, &y);
            SetRTCDateInfo(d, value, y);
            break;
        case 6:
            GetRTCDateInfo(&d, &mo, &y);
            SetRTCDateInfo(d, mo, value);
            break;
        default:
            Cmdlcd(CLEAR_LCD);
            Strlcd("Invalid Option");
            delay_ms(1000);
            break;
    }

    Cmdlcd(CLEAR_LCD);
    Strlcd("RTC Updated");
    delay_ms(1000);
}

// --- Main ---
int main(void)
{
    s32 h, m, s, d, mo, y;

    Initlcd();
    initkpm();
    RTC_Init();
    eint0_enable();
		SetRTCTimeInfo(14, 30, 0);     // 14:30:00
    SetRTCDateInfo(29, 7, 2025);   // 29/07/2025
    SetRTCDay(2);                  // 0=SUN, 1=MON, 2=TUE...

    while (1)
    {
        if (update_rtc)
        {
            update_rtc = 0;
					ShowRTCTimeUpdateMenu();
        }

        // Display RTC
        GetRTCTimeInfo(&h, &m, &s);
        GetRTCDateInfo(&d, &mo, &y);

        DisplayRTCTime(h, m, s);
        DisplayRTCDate(d, mo, y);

        delay_ms(500);
    }
}
u32 readnum(void)
{
        u32 sum=0,num=0;
        while(1)
        {
                num=key_scan();
                //cmdlcd(GOTO_LINE2_POS0+8);
                //u32lcd(num);
                if((num >0) && (num <=9))
                {
                        sum=(sum*10)+(num);
                        Cmdlcd(GOTO_LINE2_POS0);
                        U32lcd(sum);
                        while(colscan()==0);
                }
                else
                {
                        while(colscan()==0);
                        break;
                }
        }
        return sum;
}
