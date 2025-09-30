#include"types.h"
#include<lpc21xx.h>
#include"lcd_defines.h"
#include"defines.h"
#include"delay.h"

void Writelcd(u8 byte)
{
	//write any byte on lcd data pins
	//WRITEBYTE(IOPIN0,LCD_DATA,byte);
	IOPIN0=(IOPIN0&~(255<<LCD_DATA)) | (byte<<LCD_DATA);
	//select write operation
	IOCLR0=1<<LCD_RW;
	//give high to low on enable pin
	IOCLR0=1<<LCD_EN;
	delay_us(1);	
	IOSET0=1<<LCD_EN;
	delay_ms(2);
}
void Cmdlcd(u8 cmd)
{
	//select cmd.reg
	IOCLR0=1<<LCD_RS;
	//write any cmd to reg
	Writelcd(cmd);
}
void Initlcd(void)
{
	WRITEBYTE(IODIR0,LCD_DATA,0xff);
	WRITENIBBLE(IODIR0,LCD_RS,7);
	delay_ms(15);
	Cmdlcd(0x30);
	delay_ms(5);
	delay_us(100);
	Cmdlcd(0x30);
	delay_us(100);
	Cmdlcd(0x30);
	Cmdlcd(MODE_8BIT_2LINE);
	Cmdlcd(DSP_ON_CUR_OFF);
	//Cmdlcd(DSP_ON_CUR_BLINK);
	//Cmdlcd(CLEAR_LCD);
	//Cmdlcd(SHIFT_CUR_RIGHT);
}
void Charlcd(u8 asciival)
{
	//select data reg
	IOSET0=1<<LCD_RS;
	//write any ascci value to ddram
	Writelcd(asciival);
}
void Strlcd(s8 *p)
{
		while(*p)
		Charlcd(*p++);
}
void U32lcd(u32 n)
{
  u8 a[10];
  s32 i=0;
	
  if(n==0)
  {
    Charlcd('0');
  }
  else
  {
    while(n)
    {
     a[i]=(n%10)+48;
     n/=10;
     i++;
    }
    for(--i;i>=0;i--)
    {
      Charlcd(a[i]);
    }
  }
}
void S32lcd(s32 n)
{
  if(n<0)
  {
    Charlcd('-');
    n=-n;
  } 
  U32lcd(n);
}

void F32lcd(f32 fN,u32 nDP)
{
  u32 n,i;
  if(fN<0)
  {
    Charlcd('-');
    fN=-fN; 
  }
  n=fN;
  U32lcd(n);
  Charlcd('.');
  for(i=0;i<nDP;i++)
  {
    fN=(fN-n)*10;
    n=fN;
    Charlcd(n+48);
  }
}


