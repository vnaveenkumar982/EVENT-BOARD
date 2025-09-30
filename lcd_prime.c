#include<lpc21xx.h>
#include"delay.h"
#include"lcd_defines.h"
#include"lcd .h"
#include<stdlib.h>
u32 i,isprime,j,seed=1;
int checkprime(int n);
int main()
{
	u32 arr[20];
	Initlcd();
	for(i=0;i<20;i++)
	{
		arr[i]=(rand()%100)+1;
		srand(seed++);
	}
	for(i=0;i<20;i++)
	{
		isprime=1;
		if(arr[i]<2)
				isprime=0;
		else
		{
		for(j=2;j<arr[i];j++)
		{
			if(arr[i] % j == 0)
				{
					isprime = 0;
					break;
				}
		}
		}
	if(isprime)
	{
			Cmdlcd(GOTO_LINE1_POS0);
			U32lcd(arr[i]);
			delay_ms(100);         
			Cmdlcd(CLEAR_LCD);
	}
	}
	while(1);
}
