#include"types.h"
#include"delay.h"
#include"seg.h"
main()
{
	u32 sec,dly;
	init_7segs();
	while(1)
	{
		for(sec=0;sec<60;sec++)
		{
			for(dly=50;dly>0;dly--)
			{
				disp_2_mux_segs(sec);
			}
		}
	}	
}
