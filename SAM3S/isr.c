#include ".\cpu.h"

ISR_ST_UART0_FIFO volatile ISR_Uart0_Buff;


void UART0_Handler(void)
{
	uint32_t uart0_status;
	uart0_status= UART_GET_STATUS(UART0);
	if((uart0_status&UART_SR_RXRDY)==UART_SR_RXRDY)
	{
		if(ISR_Uart0_Buff.Tail>=ISR_SZ_UART0_BUFF){ISR_Uart0_Buff.Tail=0;}
		ISR_Uart0_Buff.Buff[ISR_Uart0_Buff.Tail++]=(uint8_t)UART_GET_RXDATA(UART0);
	}
	UART_RST_RXSTATUS(UART0);	
}
