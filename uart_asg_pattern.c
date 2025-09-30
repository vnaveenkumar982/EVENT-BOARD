#include "uart.h"
#include "types.h"
u32 i,j;
int main()
{
	Init_uart();
	
	for(i=0;i<=4;i++)
	{
		for(j=i;j<=4;j++)
		{
			uart_tx('*');
		}
		//uart_tx('\r');
		uart_tx('\n');
	}
	while(1);
}
