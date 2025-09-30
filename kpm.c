#include"types.h"
#include<lpc21xx.h>
#include"defines.h"
#include"kpm.h"
#include"kpm_defines.h"
#include"lcd .h"

u8 kpmlut[4][4] = {
    {'7', '8', '9', '*'},
    {'4', '5', '6', '&'},
    {'1', '2', '3', '-'},
    {'B', '0', '=', '+'}
};
void initkpm(void)
{
        //cfg row lines as gpioout
        //WRITENIBBLE(IODIR1,ROW0,15);
				IODIR1|=15<<ROW0;
}
u32 colscan(void)
{
        u32 t;
        //t=READNIBBLE(IOPIN1,COL0);
				t=((IOPIN1>>COL0)&15);
        return (t<15)?0:1;
}
u32 rowcheck(void)
{
        u32 r;
        for(r=0;r<=3;r++)
        {
                //WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
                IOPIN1=(IOPIN1&~(15<<ROW0)) |  (~(1<<r)<<ROW0);
								if(colscan()==0)
                {
                        break;
                }
        }

        //WRITENIBBLE(IOPIN1,ROW0,0);
        IOPIN1=(IOPIN1&~(15<<ROW0));
				return r;
}
u32 colcheck(void)
{
        u32 c;
        for(c=0;c<=3;c++)
        {
                //if(READBIT(IOPIN1,COL0+c)==0)
            if(((IOPIN1>>(COL0+c))&1)==0)    
						break;
        }
        return c;
}
u32 key_scan(void)
{
        u32 r,c,keyv;
        while(colscan());
        r=rowcheck();
        c=colcheck();
        keyv=kpmlut[r][c];
        return keyv;
}

