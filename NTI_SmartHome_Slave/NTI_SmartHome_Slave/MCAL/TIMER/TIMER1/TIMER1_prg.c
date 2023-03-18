
#include "TIMER1_int.h"

/*
 * Timer1.c
 *
 * Created: 3/1/2023 9:18:14 PM
 *  Author: PC
 */ 





void (*TIMER1_OV_CallBack) (void) ;
void (*TIMER1_CTC_A_CallBack) (void) ;
void (*TIMER1_CTC_B_CallBack) (void) ;
void (*TIMER1_IC_Callback)(void);



void TIMER1_void_Init(void)
{
	// set prescaler 
	TCCR1B  &= T1_PRESCALER_MASK ;
	TCCR1B  |= T1_PRESCALER  ;
	
	#if(TIMER1_MODE == TIMER1_NORMAL)
	CLEAR_BIT(TCCR1A, 0);
	CLEAR_BIT(TCCR1A, 1);
	CLEAR_BIT(TCCR1A, 4);
	CLEAR_BIT(TCCR1A, 5);
	CLEAR_BIT(TCCR1A, 6);
	CLEAR_BIT(TCCR1A, 7);
	CLEAR_BIT(TCCR1B,3);
	CLEAR_BIT(TCCR1B,4);
	
	#elif(TIMER1_MODE == TIMER1_CTC)
	CLEAR_BIT(TCCR1A, 0);
	CLEAR_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	CLEAR_BIT(TCCR1B, 4);
	#elif(TIMER1_MODE == TIMER1_FAST_PWM_10BIT )
	SET_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	CLEAR_BIT(TCCR1B, 4);
	#elif(TIMER1_MODE == TIMER1_FAST_PWM_OCR1A )
	SET_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	SET_BIT(TCCR1B, 4);
	
	#elif(TIMER1_MODE == TIMER1_PHASE_PWM )
	SET_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	CLEAR_BIT(TCCR1B, 3);
	CLEAR_BIT(TCCR1B, 4);
	#elif (TIMER1_MODE == TIMER1_FAST_PWM_ICR1)
	CLEAR_BIT(TCCR1A, 0);
	SET_BIT(TCCR1A, 1);
	SET_BIT(TCCR1B, 3);
	SET_BIT(TCCR1B, 4);
	
	#endif
	
/*
	#if(TIMER1_PRESCALER == TIMER1_DIV_BY_1)
	SET_BIT(TCCR1B , 0);
	CLEAR_BIT(TCCR1B , 1);
	CLEAR_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_DIV_BY_8)
	CLEAR_BIT(TCCR1B , 0);
	SET_BIT(TCCR1B , 1);
	CLEAR_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_DIV_BY_64 )
	SET_BIT(TCCR1B , 0);
	SET_BIT(TCCR1B , 1);
	CLEAR_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_DIV_BY_256 )
	CLEAR_BIT(TCCR1B , 0);
	CLEAR_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_DIV_BY_1024 )
	SET_BIT(TCCR1B , 0);
	CLEAR_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_EXT_FALLING )
	CLEAR_BIT(TCCR1B , 0);
	SET_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#elif(TIMER1_PRESCALER == TIMER1_EXT_RISING )
	SET_BIT(TCCR1B , 0);
	SET_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#endif*/
	
	#if(TIMER1_COM_EVENT == TIMER1_NO_ACTION)
	CLEAR_BIT(TCCR1A , 4);
	CLEAR_BIT(TCCR1A , 5);
	CLEAR_BIT(TCCR1A , 6);
	CLEAR_BIT(TCCR1A , 7);
	#elif(TIMER1_COM_EVENT == TIMER1_TOGGLE)
		#if(TIMER1_CTC_CHANNEL ==TIMER1_CHANNEL_A)
		SET_BIT(TCCR1A , 6);
		CLEAR_BIT(TCCR1A , 7);
		#elif(TIMER1_CTC_CHANNEL==TIMER1_CHANNEL_B)
		SET_BIT(TCCR1A , 4);
		CLEAR_BIT(TCCR1A , 5);
		#endif
	#elif(TIMER1_COM_EVENT == TIMER1_CLEAR )
	#if(TIMER1_CTC_CHANNEL==TIMER1_CHANNEL_A)
	CLEAR_BIT(TCCR1A , 6);
	SET_BIT(TCCR1A , 7);
	#elif(TIMER1_CTC_CHANNEL==TIMER1_CHANNEL_B)
	CLEAR_BIT(TCCR1A , 4);
	SET_BIT(TCCR1A , 5);
	#endif
	#elif(TIMER1_COM_EVENT == TIMER1_SET )
	#if(TIMER1_CTC_CHANNEL==TIMER1_CHANNEL_A)
	SET_BIT(TCCR1A , 6);
	SET_BIT(TCCR1A , 7);
	#elif(TIMER1_CTC_CHANNEL==TIMER1_CHANNEL_B)
	SET_BIT(TCCR1A , 4);
	SET_BIT(TCCR1A , 5);
	#endif
	#endif
	
	// input Capture Edge Select
	#if (ICU_EDGE == RISING)
	    SET_BIT(TCCR1B,ICES1) ;
	#elif (ICU_EDGE == FALLING)
	 CLEAR_BIT(TCCR1B,ICES1) ;
	#endif
	
	/*Disable Interrupts*/
	CLEAR_BIT(TIMSK , 2);
	CLEAR_BIT(TIMSK , 3);
	CLEAR_BIT(TIMSK , 4);
	CLEAR_BIT(TIMSK , 5);
	/*CLEAR FLAGS*/
	SET_BIT(TIFR , 2);
	SET_BIT(TIFR , 3);
	SET_BIT(TIFR , 4);
	SET_BIT(TIFR , 5);
	/*Clear register*/
	TCNT1 = 0 ;
	OCR1A = 0 ;
	OCR1B = 0 ;
	
	
}


void TIMER1_void_SetTimerReg(u16 Copy_uint16Val)
{
	TCNT1= Copy_uint16Val ;
}


void TIMER1_void_SetCompare_A_Val(u16 Copy_uint16Val) 
{
	OCR1A = Copy_uint16Val ;
}
void TIMER1_void_SetCompare_B_Val(u16 Copy_uint16Val) 
{
	OCR1B = Copy_uint16Val ;
}
void TIMER1_void_EnableOVInt(void) 
{
	SET_BIT(TIMSK,TOIE1) ;
}
void TIMER1_void_DisableOVInt(void) 
{
	CLEAR_BIT(TIMSK,TOIE1) ;
}
void TIMER1_void_EnableCTC_A_Int(void) 
{
	SET_BIT(TIMSK,OCIE1A);
}

void TIMER1_void_EnableICInt(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void TIMER1_void_EnableCTC_B_Int(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void TIMER1_void_DisableCTC_A_Int(void) 
{
	CLEAR_BIT(TIMSK,OCIE1A);
}
void TIMER1_void_DisableCTCBInt(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}
void TIMER1_void_DisableICInt(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}


void TIMER1_void_SetOVCallBack(void (*Copy_ptr) (void) ) 
{
	if(Copy_ptr!= NULL)
	{
		TIMER1_OV_CallBack= Copy_ptr ;
	}
}

void TIMER1_void_SetCTCACallBack(void (*Copy_ptr) (void) ) 
{
	if(Copy_ptr != NULL)
	{
		TIMER1_CTC_A_CallBack =Copy_ptr ;
	}
}
void TIMER1_void_SetCTCBCallBack(void (*Copy_ptr) (void) ) 
{
	if(Copy_ptr != NULL)
	{
		TIMER1_CTC_B_CallBack = Copy_ptr ;
	}
	
}
void TIMER1_void_SetCAPTURECallBack(void (*Copy_ptr) (void) ) 
{
	
	if(Copy_ptr != NULL)
	{
		TIMER1_IC_Callback= Copy_ptr ;
	}
}

void __vector_6(void)
{ 
	if(TIMER1_IC_Callback != NULL)
	{
		TIMER1_IC_Callback();
	}
}
void __vector_7(void) 
{
	if(TIMER1_CTC_A_CallBack != NULL)
	{
		TIMER1_CTC_A_CallBack();
	}
}
void __vector_8(void)
{
	if(TIMER1_CTC_B_CallBack != NULL)
	{
		TIMER1_CTC_B_CallBack();
	}
}
void __vector_9(void)
{
	if(TIMER1_OV_CallBack != NULL)
	{
		TIMER1_OV_CallBack();
	}
}

void ICU_voidSetSignalch(u8 state) 
{  

	if(state == FALLING)
	{
		CLEAR_BIT(TCCR1B,ICES1) ;
	}
	else if (state == RISING)
	{
		SET_BIT(TCCR1B,ICES1) ;
	}
}