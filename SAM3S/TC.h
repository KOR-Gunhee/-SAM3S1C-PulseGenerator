/*
 * TC.h
 *
 * Created: 2019-01-18 오전 11:53:08
 *  Author: ghhan
 */ 


#ifndef TC_H_
#define TC_H_


#define TIOA 15
#define TIOB 16

void TC_Pulse(Tc *P_Tc, uint32_t ul_channel, uint32_t ul_mode);
void TCInit();


#endif /* TC_H_ */