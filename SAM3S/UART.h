/*
 * UART.h
 *
 * Created: 2018-01-05 오전 9:34:15
 *  Author: ghhan
 */ 


#ifndef UART_H_
#define UART_H_

#include "sam.h"

#define URXD0 9
#define UTXD0 10
#define RSTRX 2
#define RSTTX 3
#define RSTSTA 8
#define RXDIS 5
#define TXDIS 7
#define TXEN 6
#define RXEN 4
#define CHMODE 14
#define PAR 9
#define TXRDY 1
#define RXRDY 0

#define UART_GET_STATUS(puart)  ((puart)->UART_SR)
#define UART_GET_RXDATA(puart) ((puart)->UART_RHR)
#define UART_RST(tx,rx,state) ((((tx)&1)<<3)|(((rx)&1)<<2)| (((state)&1)<<8))
#define UART_RST_RXSTATUS(puart) (puart)->UART_CR=UART_RST(0,0,1)

extern char UART_Buff[32];
extern int UART_msg_lengh;

void UARTInit(void);
void UARTStart(void);
void SendByte(unsigned char ch);
int SendString(const char *S_str);
uint32_t ReadByte(uint16_t *data);
uint32_t receive(void);
int GetString(uint8_t *data);

#endif /* UART_H_ */