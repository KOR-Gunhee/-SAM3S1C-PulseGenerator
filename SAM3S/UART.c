#include ".\cpu.h"


ISR_ST_UART0_FIFO volatile *puart_fifo=0;

char UART_Buff[32];
int UART_msg_lengh = 0;

void UARTInit(void)
{
	UART0->UART_CR=((1<<RSTTX)|(1<<RSTRX)|(1<<RSTSTA));
	UART0->UART_CR=((1<<RXDIS)|(1<<TXDIS));
	UART0->UART_BRGR=(SystemCoreClock)/(16*115200);
	UART0->UART_MR=(0<<CHMODE)|(4<<PAR);
	

	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	UART0->UART_CR=(1<<TXEN)|(1<<RXEN);
//	UART0->UART_IDR=UART_IDR_ENDRX;
	UART0->UART_IER=UART_IER_RXRDY;
}

void SendByte(unsigned char ch)
{
	while((UART0->UART_SR&(1<<TXRDY))==0);

	UART0->UART_THR=ch;
}

int SendString(const char *S_str)
{
	while(*S_str)
	{
		SendByte(*S_str);
		S_str++;
	}
	return 0;
}

uint32_t receive(void)
{
	while((UART0->UART_SR&(1<<RXRDY))==0);
	return UART0->UART_RHR;
}

uint32_t ReadByte(uint16_t *data)
{  
	 
	if((UART0->UART_SR&(1<<RXRDY))==0)
	return 1;

	*data = (uint16_t)UART0->UART_RHR;
	return 0;
}

int GetString(uint8_t *data)
{
	int szbuff=0;
	
	if(ISR_Uart0_Buff.Head==ISR_Uart0_Buff.Tail)return 0;
	puart_fifo=&ISR_Uart0_Buff;
	szbuff=ISR_SZ_UART0_BUFF;
	
	if(puart_fifo->Head>=szbuff){puart_fifo->Head=0;}
	
	if (puart_fifo->Buff[puart_fifo->Head]==13)
	{
		*data=puart_fifo->Buff[puart_fifo->Head++];
		SendString("\r\n");
		SendString("Selected MODE : ");
		for (volatile int a =0; a<=UART_msg_lengh-1;a++)
		{
			SendByte(UART_Buff[a]);
			if (a==UART_msg_lengh-1)
			{
				SendString("\r\n");
				UART_msg_status = 1;
				break;
			}
		}
	}
	else
	{
		*data=puart_fifo->Buff[puart_fifo->Head++];
		UART_Buff[UART_msg_lengh]=(char)*data;
		SendByte(UART_Buff[UART_msg_lengh++]);
	}
	return 1;
}