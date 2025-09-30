#include "uart.h"
#include "delay.h"
#include "uart_defines.h"
int main()
{
	Init_uart();
	while(1)
	{
	uart_str("Welcome To Vector");
	//uart_tx('\n');
	delay_ms(500);
	}
}
