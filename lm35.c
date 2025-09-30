//lm35.c//
#include"types.h"
#include"adc_defines.h"
#include"adc.h"
u32 tdegc;
u32 Read_LM35(void)
{
	f32 ear;  // Variable to store analog voltage (in volts)
	u32 dval; // Variable to store raw 10-bit digital value from ADC
	static u32 flag=0; // Static flag to initialize ADC only once
	if(flag==0)
	{
		Init_ADC();
		flag=1;
	}
	Read_ADC(1,&ear,&dval);
	tdegc=ear*100;
	return tdegc;
}

