
#ifndef TIMER1_H_
#define TIMER1_H_

#include "..\..\DIO\dio.h"  //DIO
#include "..\..\..\LIB\std_types.h"
#include "..\..\..\LIB\bit_math.h"
#include "TIMER1_priv.h"
#include "TIMER1_config.h"



#define  F_CPU 16000000UL


/*#define  NULL 0*/




#define  WGM10   0
#define  WGM11   1
#define  WGM12   3
#define  WGM13   4
#define  COM1B0  4
#define  COM1B1  5
#define  COM1A0  6
#define  COM1A1  7

#define T1_PRESCALER_MASK		 0xF8
#define T1_PRESCALER_DIS		 0
#define T1_PRESCALER_1			 1
#define T1_PRESCALER_8			 2
#define T1_PRESCALER_64			 3
#define T1_PRESCALER_256		 4
#define T1_PRESCALER_1024		 5
#define T1_EX_FALLING			 6
#define T1_EX_RISING			 7

#define ICNC1					7
#define  ICES1					6

#define TICIE1				 5
#define OCIE1A				 4
#define OCIE1B				 3
#define TOIE1               2

#define ICES1				6
#define  ICF1               5
#define  TOV1               2

#define TIMER1_NO_ACTION	100
#define TIMER1_TOGGLE		12
#define TIMER1_SET			20
#define TIMER1_CLEAR		25

#define TIMER1_CHANNEL_A	1
#define TIMER1_CHANNEL_B	2

#define TIMER1_NORMAL 			1
#define TIMER1_CTC 				2
#define TIMER1_FAST_PWM_10BIT	3
#define TIMER1_PHASE_PWM 		4
#define TIMER1_FAST_PWM_OCR1A 	5
#define TIMER1_FAST_PWM_ICR1    6

#define  RISING 0
#define  FALLING 1


void TIMER1_void_Init(void);
void TIMER1_void_SetTimerReg(u16 Copy_uint8Val);
void TIMER1_void_SetCompare_A_Val(u16 Copy_uint16Val) ;
void TIMER1_void_SetCompare_B_Val(u16 Copy_uint16Val) ;
void TIMER1_void_EnableOVInt(void) ;
void TIMER1_void_DisableOVInt(void) ;
void TIMER1_void_EnableCTC_A_Int(void) ;
void TIMER1_void_EnableCTC_B_Int(void) ;
void TIMER1_void_EnableICInt(void) ;
void TIMER1_void_DisableCTC_A_Int(void) ;
void TIMER1_void_DisableCTC_B_Int(void) ;
void TIMER1_void_DisableICInt(void) ;
void ICU_voidSetSignalch(u8 state) ;

void TIMER1_void_SetOVCallBack(void (*Copy_ptr) (void) ) ;

void TIMER1_void_SetCTCACallBack(void (*Copy_ptr) (void) ) ;
void TIMER1_void_SetCTCBCallBack(void (*Copy_ptr) (void) ) ;
void TIMER1_void_SetCAPTURECallBack(void (*Copy_ptr) (void) ) ;

void __vector_6(void) __attribute__((signal , used));
void __vector_7(void) __attribute__((signal , used));
void __vector_8(void)__attribute__((signal , used));
void __vector_9(void)__attribute__((signal , used));
#endif /* TIMER1_H_ */