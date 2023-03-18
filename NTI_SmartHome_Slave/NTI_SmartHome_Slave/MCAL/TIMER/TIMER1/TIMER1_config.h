/*
 * Timer1_conf.h
 *
 * Created: 3/2/2023 7:34:45 PM
 *  Author: PC
 */ 


#ifndef TIMER1_CONF_H_
#define TIMER1_CONF_H_


#include "TIMER1_int.h"

/****************************************************************/
/** !comment : Please Enter the timer_mode Reference				*/
/** 		   TIMER0_MODE can be : 						*/
/*					    					NORMAL 				*/
/*						    				PWM_PhaseCorrect 				*/
/*							    			CTC 			*/
/*                                      PWM_FastMode           */
/****************************************************************/
#define TIMER1_MODE 		TIMER1_NORMAL




/****************************************************************/
/** !comment : Please Enter the TIMER0_PRESCALER Reference				*/
/** 		   TIMER0_PRESCALER can be : 						*/
/*

											T0_Disable  ,
											F_CPU_Prescaler1,
											F_CPU_Prescaler8,
											F_CPU_Prescaler64,
											F_CPU_Prescaler256,
											F_CPU_Prescaler1024,
											F_T0_PIN_SRISING, */
/****************************************************************/

#define T1_PRESCALER  	 T1_PRESCALER_1024



/****************************************************************/
/** !comment : Please Enter the timer_mode Reference				*/
/** 		   TIMER0_MODE can be : 						*/
/*	 TIMER1_NO_ACTION
 TIMER1_TOGGLE
 TIMER1_SET
 TIMER1_CLEAR
*/
/****************************************************************/
#define TIMER1_COM_EVENT	 TIMER1_CLEAR

/****************************************************************/


/*Range
#define TIMER1_CHANNEL_A
#define TIMER1_CHANNEL_B
*/



/* timer input Capture Edge Select 
select bitween RISING 
                FALLING */
#define ICU_EDGE	RISING 

#define TIMER1_CTC_CHANNEL   TIMER1_CHANNEL_B
#endif /* TIMER1_CONF_H_ */