#include ".\cpu.h"

void PMC_Ena()
{
	//UART, CAN0, CAN1 주변장치 클럭 활성화
	PMC->PMC_PCER0|=((1<<ID_PIOA)|(1<<ID_PIOB)|(1<<ID_PIOC)|(1<<ID_TC1)|(1<<ID_UART0));
}