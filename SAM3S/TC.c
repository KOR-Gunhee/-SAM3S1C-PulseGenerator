#include ".\cpu.h"




void TC_Pulse(Tc *P_Tc, uint32_t ul_channel, uint32_t ul_mode)
 {
	 TcChannel *tc_channel;

	 tc_channel = P_Tc->TC_CHANNEL + ul_channel;

	 tc_channel->TC_CCR = TC_CCR_CLKDIS;
	 tc_channel->TC_IDR = 0xFFFFFFFF;
	 tc_channel->TC_SR;

	 tc_channel->TC_CMR = ul_mode;
 }

void TCInit()
 {
	 TC_Pulse(TC0, 1, TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_EEVT_XC0 | TC_CMR_WAVSEL_UP | TC_CMR_WAVE
	 | TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR | TC_CMR_BCPB_CLEAR | TC_CMR_BCPC_SET);
 }