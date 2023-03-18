#include "TIMER2_int.h"
volatile pf	 TIMER2_OV_CallBack ;
volatile pf  TIMER2_CTC_CallBack ;

/******* TIMER initilzation *******/
/*         ///   TCCR2  
CS20,
CS21,
CS22,
WGM21,
COM20,
COM21,
WGM20,
FOC2
*/
void TIMER2_void_Init(void)
{	/******************     TIMER2_MODE  ********************/
	#if(TIMER2_MODE == TIMER2_NORMAL)
		CLEAR_BIT(TCCR2 , WGM21);
		CLEAR_BIT(TCCR2 , WGM20);	
	#elif(TIMER2_MODE == TIMER2_CTC)
		CLEAR_BIT(TCCR2 , WGM21);
		SET_BIT(TCCR2 , WGM20);		
	#elif(TIMER2_MODE == TIMER2_FAST_PWM )
		SET_BIT(TCCR2 , WGM21);
		SET_BIT(TCCR2 , WGM20);		
	#elif(TIMER2_MODE == TIMER2_PHASE_PWM )
		SET_BIT(TCCR2 , WGM21);
		CLEAR_BIT(TCCR2 , WGM20);		
	#endif	
	/******************     TIMER2_PRESCALER  ********************/
	#if(TIMER2_PRESCALER == TIMER2_DIV_BY_1)
		SET_BIT(TCCR2 , CS20);
		CLEAR_BIT(TCCR2 , CS21);
		CLEAR_BIT(TCCR2 , CS22);	
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_8)
		CLEAR_BIT(TCCR2 , CS20);
		SET_BIT(TCCR2 , CS21);
		CLEAR_BIT(TCCR2 , CS22);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_64 )
		SET_BIT(TCCR2 , CS20);
		SET_BIT(TCCR2 , CS21);
		CLEAR_BIT(TCCR2 , CS22);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_256 )
		CLEAR_BIT(TCCR2 , CS20);
		CLEAR_BIT(TCCR2 , CS21);
		SET_BIT(TCCR2 , CS22);
	#elif(TIMER2_PRESCALER == TIMER2_DIV_BY_1024 )
		SET_BIT(TCCR2 , CS20);
		CLEAR_BIT(TCCR2 , CS21);
		SET_BIT(TCCR2 , CS22);		
	#endif
	/******************     Compare Match Output Mode  ********************/
	#if(TIMER2_COM_EVENT == TIMER2_NO_ACTION)
		CLEAR_BIT(TCCR2 , COM20);
		CLEAR_BIT(TCCR2 , COM21);	
	#elif(TIMER2_COM_EVENT == TIMER2_TOGGLE)   //REVERSED
		SET_BIT(TCCR2 , COM20)                
		CLEAR_BIT(TCCR2 , COM21);
	#elif(TIMER2_COM_EVENT == TIMER2_CLEAR )
		CLEAR_BIT(TCCR2 , COM20);
		SET_BIT(TCCR2 , COM21  );
	#elif(TIMER2_COM_EVENT == TIMER2_SET )
		SET_BIT(TCCR2 , COM20);
		SET_BIT(TCCR2 , COM21);		
	#endif
/*           TIMSK 
TIOE0,
OCIE0,
TIOE1,
OCIE1B,
OCIE1A,
TICIE1,
TIOE2,
OCIE2
*/	
	/*Disable Interrupts*/
	CLEAR_BIT(TIMSK , TIOE2);        // Timer/Counter0 Overflow Interrupt Enable	
	CLEAR_BIT(TIMSK , OCIE2);		 // Timer/Counter0 Output Compare Match Interrupt Enable
	/*CLEAR FLAGS*/
	SET_BIT(TIFR , TOV2);	   //Timer/Counter0 Overflow Flag
	SET_BIT(TIFR , OCF2);      //Output Compare Flag 0

/******       /////    TIFR       
TOV0,
OCF0,
TOV1,
OCF1B,
OCF1A,
ICFI1,
TOV2,
OCF2
******/	
	/*Clear register*/
	TCNT2 = 0 ;
	OCR2 = 0 ;
}



/**********************       TCNT =  INPUT:		VALUE                 ************************/
void TIMER2_void_SetTimerReg(u8 Copy_uint8Val)
{
	TCNT2 = Copy_uint8Val ;
}

/**********************       OCR =  INPUT:		VALUE                 ************************/
void TIMER2_void_SetCompareVal(u8 Copy_uint8Val)
{
	OCR2 = Copy_uint8Val ;
}


/******************* // Timer/Counter0 Overflow Interrupt Enable	 ************/
void TIMER2_void_EnableOVInt(void)
{
	SET_BIT(TIMSK , TIOE2);
}

/******************* // Timer/Counter0 Overflow Interrupt DISABLE	 ************/
void TIMER2_void_DisableOVInt(void)
{
	CLEAR_BIT(TIMSK , TIOE2);
}
void TIMER2_void_EnableCTCInt(void)
{
	SET_BIT(TIMSK , OCIE2);
}
void TIMER2_void_DisableCTCInt(void)
{
	CLEAR_BIT(TIMSK , OCIE2);
}
/***********************  CALL BACK FN ************/
void TIMER2_void_SetOVCallBack(pf Copy_ptr)
{
	if(Copy_ptr != NULL)
	{
		TIMER2_OV_CallBack = Copy_ptr ;
	}		
}


// (void (*Copy_ptr) (void) ) 
void TIMER2_void_SetCTCCallBack( pf Copy_ptr) 
{
	if(Copy_ptr != NULL)
	{
			TIMER2_CTC_CallBack = Copy_ptr ;
	}	
}



void __vector_5(void) __attribute__((signal , used));
void __vector_5(void)
{
	
	TIMER2_OV_CallBack();
}

void __vector_4(void) __attribute__((signal , used));
void __vector_4(void)
{
	
	TIMER2_CTC_CallBack();
}
