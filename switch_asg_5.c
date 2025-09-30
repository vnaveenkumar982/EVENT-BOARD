#include<LPC21xx.h>
#define LED_0 0
#define SW1_16 16
#define SW2_17 17
main()
{
	int cnt=0;
	IODIR0|=0xff<<LED_0;
	IOSET0=0x0f<<LED_0;
	while(1)
	{
		 if (((IOPIN0 >> SW1_16) & 1) == 0) 
			 {
				 if(cnt<255)
				 {
					 cnt++;
				 }
            while (((IOPIN0 >> SW1_16) & 1) == 0); 
					IOPIN0=(IOPIN0&(~(255<<LED_0)) | ((cnt^0x0f)<<LED_0));
         }

       
        else if (((IOPIN0 >> SW2_17) & 1) == 0) 
				{
					if(cnt>=0)
					{
						cnt--;
					}
            while (((IOPIN0 >> SW2_17) & 1) == 0); 
					IOPIN0=(IOPIN0&(~(255<<LED_0)) | ((cnt^0x0f)<<LED_0));              
        }
	}
}
		
