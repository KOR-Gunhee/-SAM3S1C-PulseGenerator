/*
 * isr.h
 *
 * Created: 2018-07-27 오후 2:22:41
 *  Author: DEV_PC
 */ 


#ifndef ISR_H_
#define ISR_H_

#define ISR_SZ_UART0_BUFF 32

typedef struct{
	uint32_t  Head;
	uint32_t  Tail;
	uint8_t   Buff[ISR_SZ_UART0_BUFF];
}ISR_ST_UART0_FIFO;


extern ISR_ST_UART0_FIFO volatile ISR_Uart0_Buff;


#endif /* ISR_H_ */