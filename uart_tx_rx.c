#include "uart.h"
#include "delay.h"
int main()
{
	u8 ch;
	Init_uart();
	while(1)
	{
		ch=uart_rx();
		uart_tx(ch);	
	}
}
