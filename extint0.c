////extint0.c/////
#include <LPC21xx.h>
#include "eint.h"
#include "types.h"

#define EINT0_CH_NO 14
#define LED 8
#define LED_RED 27
#define LED_GREEN 30
#define PIN_FUNC4 3
#define EINT0_PIN_FUNC PIN_FUNC4

extern u8 admin_flag;
void eint0_enable(void);  // Function to initialize EINT0

void cfgportpin(u32 portno,s32 pinno,u32 pinfunc);


void eint0_isr(void) __irq
{
		IOCLR1=1<<LED_RED;
		IOCLR1=1<<LED_GREEN;
    admin_flag = 1;         // Set flag to enter admin mode
    EXTINT = 1 << 0;        // Clear EINT0 flag
    VICVectAddr = 0;        // Acknowledge interrupt
}

void eint0_enable(void)
{
    IODIR0 |= 1 << LED;
		cfgportpin(0, 1, EINT0_PIN_FUNC);
    VICIntSelect &= ~(1 << EINT0_CH_NO);
    VICIntEnable |= (1 << EINT0_CH_NO);
    VICVectCntl0 = (1 << 5) | EINT0_CH_NO;
    VICVectAddr0 = (unsigned long)eint0_isr;

    EXTINT = 1 << 0;
    EXTMODE = 1 << 0;       // Edge sensitive
    EXTPOLAR &= ~(1 << 0);  // Falling edge
}
