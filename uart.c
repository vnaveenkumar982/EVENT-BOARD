#include <lpc21xx.h>
#include "uart_defines.h"
#include "types.h"

void Init_uart(void)
{
	//cnfg p0.0 as TXD bit and p0.1 as RXD bit
	PINSEL0=0x00000005;
	//set dlab to acess U0DLL & U0DLM
	U0LCR=1<<DLAB_BIT |WORD_LEN_8BITS;
	U0DLL=DIVISOR;
	U0DLM=DIVISOR>>8;
	//clear DLAB BIT to freez the U0DLL&U0DLM
	U0LCR&=~(1<<DLAB_BIT);
}
void uart_tx(u8 sdat)
{
	//transmit sdata
	U0THR=sdat;
	//checking the transmission complete
	while(((IOPIN0>>TEMT_BIT)&1)==0);
}
u8 uart_rx(void)
{
	//checking the data reception status
	while(((IOPIN0>>RDR)&1)==0);
	//return the data which is present in U0RBR
	return U0RBR;
}

void uart_str(s8 *p)
{
	while(*p)
	uart_tx(*p++);
}
