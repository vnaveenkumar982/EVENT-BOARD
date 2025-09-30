#include<LPC21xx.h>
#include"types.h"
#include"pin_connect_block.h"
#include"adc_defines.h"
#include"delay.h"
void Init_ADC(void)
{
        //cfg p0.28 s ANO pin
        cfgportpin(0,28,ANO_INPUT_PIN);
        //cfg ADCR sfrn
        ADCR=(1<<PDN_BIT) | (CLKDIV<<CLKDIV_BITS);
}
void Read_ADC(u8 chno,f32 *eAR,u32 *dval)
{
        //clear any prev channel selection
        ADCR&=0xffffff00;
        //select analog channel,start now
        ADCR|=(1<<ADC_START_BIT) | (1<<chno);
        //conversion time
        delay_us(3);
        //wait untill con completion status
        while(((ADDR>>DONE_BIT)&1)==0);
        //stop adc coversion
        ADCR&=~(1<<ADC_START_BIT);
        //reading the 10 bit digital data
        *dval=((ADDR>>RESULT_BITS)&1023);
        //representing in float /real number
        *eAR=(*dval *(3.3/1023));
}
