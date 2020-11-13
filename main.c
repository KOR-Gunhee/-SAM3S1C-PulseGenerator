/*
 * PulseGenerator.c
 *
 * Created: 2019-01-07 오전 8:37:37
 * Author : ghhan
 */ 


#include "mainh.h"

int UART_msg_status=0;

void MyDelay(volatile uint32_t delay)
{
	while(delay)
	{
		delay--;
	}
}

void MyDelay2(volatile uint32_t delay1,volatile uint32_t delay2)
{
	while(delay1)
	{
		MyDelay(delay2);
		delay1--;
	}
}

void Showlist()
{
	SendString("--------Select to MODE---------\r\n");
	SendString("1 : 5k Pulse\r\n");
	SendString("2 : 10k Pulse\r\n");
	SendString("3 : 13k Pulse\r\n");
	SendString("4 : 16k Pulse\r\n");
	SendString("5 : STOP Pulse\r\n");
	SendString("--------------------------------\r\n");
}

void Clock_Sel(uint16_t num)
{
	if (num==1)
	{
		SendString("Output Pulse : 5k\r\n");
		//5k Hz
		TC0->TC_CHANNEL[1].TC_RC = 1600;
		TC0->TC_CHANNEL[1].TC_RA = 800;
		TC0->TC_CHANNEL[1].TC_RB = 800;
		
		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN|TC_CCR_SWTRG;

		Showlist();
	}

	else if (num==2)
	{
		SendString("Output Pulse : 10k\r\n");
		//10k Hz
		TC0->TC_CHANNEL[1].TC_RC = 800;
		TC0->TC_CHANNEL[1].TC_RA = 400;
		TC0->TC_CHANNEL[1].TC_RB = 400;

		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN|TC_CCR_SWTRG;

		Showlist();
	}

	else if (num==3)
	{
		SendString("Output Pulse : 13k\r\n");
		//13k Hz
		TC0->TC_CHANNEL[1].TC_RC = 615;
		TC0->TC_CHANNEL[1].TC_RA = 307;
		TC0->TC_CHANNEL[1].TC_RB = 307;

		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN|TC_CCR_SWTRG;

		Showlist();
	}

	else if (num==4)
	{
		SendString("Output Pulse : 16k\r\n");
		//16k Hz
		TC0->TC_CHANNEL[1].TC_RC = 500;
		TC0->TC_CHANNEL[1].TC_RA = 250;
		TC0->TC_CHANNEL[1].TC_RB = 250;

		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN|TC_CCR_SWTRG;

		Showlist();
	}

	else if (num==5)
	{
		SendString("Stop Pulse\r\n");
		TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS;

		Showlist();
	}

	else 
	{
		Showlist();
	}

	char UART_Buff[32]={0,};
	UART_msg_lengh=0;
	UART_msg_status=0;
}

void BoardInit()
{
	WDT->WDT_MR=(1<<15);
 
 	SystemInit();
		
	__disable_irq();
		
	PIOInit();

	PMC_Ena();
	
	UARTInit();
	
 	TCInit();

	__enable_irq();
}

int main(void)
{
	uint8_t  byte01;	

    /* Initialize the SAM system */
    BoardInit();	
	
	SendString("Default Pulse : 10k\r\n");
	//base pulse 10k
	TC0->TC_CHANNEL[1].TC_RC = 800;
	TC0->TC_CHANNEL[1].TC_RA = 400;
	TC0->TC_CHANNEL[1].TC_RB = 400;

	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN|TC_CCR_SWTRG;

	//10sec delay
	MyDelay2(10000,5000);

	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS;

	Showlist();
    /* Replace with your application code */
    while (1) 
    {
		if(GetString(&byte01)>0)
		{	
			if (UART_msg_status==1)
			{
				Clock_Sel(atoi(UART_Buff));
			}
		}
    }
}
