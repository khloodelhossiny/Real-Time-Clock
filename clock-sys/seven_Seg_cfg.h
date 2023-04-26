/*
 * seven_Seg_cfg.h
 *
 * Created: 11/18/2022 1:03:00 PM
 *  Author: safifi
 */ 


#ifndef SEVEN_SEG_CFG_H_
#define SEVEN_SEG_CFG_H_
#include "std_macros.h"

#define SS_ANODE
#define SEVEN_SEG_INIT_PORTS() DDRB |= 0x7f; PORTB = 0x7f; SETBIT(DDRA,0); SETBIT(DDRA,1); SETBIT(DDRA,2); SETBIT(DDRA,3); SETBIT(DDRA,4); SETBIT(DDRA,5); 
#define SS_PORT PORTB

#ifdef SS_ANODE
	#define EN1_DIS() CLRBIT(PORTA,0);
	#define EN1_EN()  SETBIT(PORTA,0);
	#define EN2_DIS() CLRBIT(PORTA,1);
	#define EN2_EN()  SETBIT(PORTA,1);
	#define EN3_DIS() CLRBIT(PORTA,2);
	#define EN3_EN()  SETBIT(PORTA,2);
	#define EN4_DIS() CLRBIT(PORTA,3);
	#define EN4_EN()  SETBIT(PORTA,3);
	#define EN5_DIS() CLRBIT(PORTA,4);
	#define EN5_EN()  SETBIT(PORTA,4);
	#define EN6_DIS() CLRBIT(PORTA,5);
	#define EN6_EN()  SETBIT(PORTA,5);
	
#else
	#define EN1_DIS() SETBIT(PORTA,0);
	#define EN1_EN()  CLRBIT(PORTA,0);
	#define EN2_DIS() SETBIT(PORTA,1);
	#define EN2_EN()  CLRBIT(PORTA,1);
	#define EN3_DIS() SETBIT(PORTA,2);
	#define EN3_EN()  CLRBIT(PORTA,2);
	#define EN4_DIS() SETBIT(PORTA,3);
	#define EN4_EN()  CLRBIT(PORTA,3);
	#define EN5_DIS() SETBIT(PORTA,4);
	#define EN5_EN()  CLRBIT(PORTA,4);
	#define EN6_DIS() SETBIT(PORTA,5);
	#define EN6_EN()  CLRBIT(PORTA,5);
	
#endif
#endif /* SEVEN_SEG_CFG_H_ */