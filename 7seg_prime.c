#include <lpc21xx.h>
#include "delay.h"
#include "types.h"

#define CA_7SEG 8
#define DSEL1 16
#define DSEL2 17

const u8 seglut[]=
{
	0xc0,0xf9,0xa4,0xb0,0x99,
	0x92,0x82,0xf8,0x80,0x90
};
void disp_2mux(u8 n);
int checkprime(int n);

s32 i,dly;
int main()
{
	IODIR0|=255<<CA_7SEG;
	IODIR0|=(1<<DSEL1) | (1<<DSEL2);
	for(i=0;i<=99;i++)
	{
		if(checkprime(i))
		{
			for(dly=100;dly>=0;dly--)
			{
				disp_2mux(i);
			}
		}
	}
}
int checkprime(int n)
{
	int i;
	for(i=2;i<n;i++)
	{
		if(n%i==0)
		{
			return 0;
		}
	}
	return i;
}

void disp_2mux(u8 n)
{
	IOPIN0=(IOPIN0&~(255<<CA_7SEG)) | (seglut[n/10]<<CA_7SEG);
	IOSET0=1<<DSEL1;
	delay_ms(1);
	IOCLR0=1<<DSEL1;
	
	IOPIN0=(IOPIN0&~(255<<CA_7SEG)) | (seglut[n%10]<<CA_7SEG);
	IOSET0=1<<DSEL2;
	delay_ms(1);
	IOCLR0=1<<DSEL2;
}
/*

#include <lpc21xx.h>
#include "delay.h"
#include "types.h"

#define CA_7SEG 8
#define DSEL1 16
#define DSEL2 17

const u8 seglut[] =
{
    0xC0,0xF9,0xA4,0xB0,0x99,
    0x92,0x82,0xF8,0x80,0x90
};

void disp_2mux(u8 num);
void fibo_series(void);

s32 i, dly;

int main()
{
    IODIR0 |= (0xFF << CA_7SEG) | (1 << DSEL1) | (1 << DSEL2);

    while(1)
    {
        fibo_series();
    }
}

void disp_2mux(u8 num)
{
    IOPIN0 = (IOPIN0 & ~(0xFF << CA_7SEG)) | (seglut[num / 10] << CA_7SEG);
    IOSET0 = 1 << DSEL1;
    delay_ms(2);
    IOCLR0 = 1 << DSEL1;

    IOPIN0 = (IOPIN0 & ~(0xFF << CA_7SEG)) | (seglut[num % 10] << CA_7SEG);
    IOSET0 = 1 << DSEL2;
    delay_ms(2);
    IOCLR0 = 1 << DSEL2;
}

void fibo_series(void)
{
    int a = 0, b = 1, next;

        for(dly = 100; dly >=0; dly--)
        disp_2mux(a);

        for(dly = 100; dly >=0; dly--)
        disp_2mux(b);

    while(1)
    {
        next = a + b;
        if(next > 99) break;

        for(dly = 100; dly >=0; dly--)
            disp_2mux(next);

        a = b;
        b = next;
    }
}

*/
