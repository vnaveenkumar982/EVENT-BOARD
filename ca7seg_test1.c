/*#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"defines.h"
#define CA7SEG_0_0  0
const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x90,0x80
};
u32 i;
main()
{
	//cnf p0.0 to p0.7 as gpio out pins 
	WRITEBYTE(IODIR0,CA7SEG_0_0,0XFF);
	for(i=0;i<9;i++)
	{
		WRITEBYTE(IOPIN0,CA7SEG_0_0,seglut[i]);
		delay_s(1);
	}
}
*/

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"

#define CA7SEG_0_0  0   //P0.0–P0.7

const u8 seglut[] =
{
  0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};

u32 i, count;

int main(void)
{
    // Configure P0.0 to P0.7 as output
    WRITEBYTE(IODIR0, CA7SEG_0_0, 0xFF);

    while (1)
    {
        // Clockwise rotation (5 times)
        for (count = 0; count < 5; count++)
        {
            for (i = 0; i < 7; i++)
            {
                WRITEBYTE(IOPIN0, CA7SEG_0_0, 0xff^seglut[i]);
                delay_ms(500);
            }
        }

        // Anticlockwise rotation (5 times)
        for (count = 0; count < 5; count++)
        {
            for (i = 7; i > 0; i--)
            {
                WRITEBYTE(IOPIN0, CA7SEG_0_0, seglut[i - 1]);
                delay_ms(500);
            }
        }
    }
}
