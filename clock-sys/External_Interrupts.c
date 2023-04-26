/*
 * External_Interrupts.c
 *
 * Created: 2/13/2023 8:05:24 PM
 *  Author: Ve-ga
 */ 
#include "External_Interrupts.h"
void INT0_init(void){
	GICR = 1<<INT0;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	SETBIT(SREG, 7);
	
}