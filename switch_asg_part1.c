#include <LPC21xx.h>

#define LED_0 0
#define LED_1 1
#define LED_2 2
#define LED_3 3
#define LED_4 4
#define LED_5 5
#define LED_6 6
#define LED_7 7

#define SW_1 16
#define SW_2 17
#define SW_3 18
#define SW_4 19

int main()
{
    while(1)
    {
        IODIR0 |= 0xFF << LED_0;
        IOCLR0 = 0x0F << LED_0;
        IOSET0 = 0xF0 << LED_0;  

       
        if (((IOPIN0 >> SW_1) & 1) == 0)
        {
           IOPIN0=(IOPIN0&(~(255<<LED_0))) | ((1<<0) | (1<<7))^0x0f)<<LED_0;
        }

        
        /*if (((IOPIN0 >> SW_2) & 1) == 0)
        {
            IOPIN0 |= 1 << LED_1;
            IOPIN0 &= ~(1 << LED_6);
        }

        
        if (((IOPIN0 >> SW_3) & 1) == 0)
        {
            IOPIN0 |= 1 << LED_2;
            IOPIN0 &= ~(1 << LED_5);
        }

        
        if (((IOPIN0 >> SW_4) & 1) == 0)
        {
            IOPIN0 |= 1 << LED_3;
            IOPIN0 &= ~(1 << LED_4);
        }*/
    }
}
