
#ifndef _TIMER2_PRIV
#define _TIMER2_PRIV

#define TCNT2	 (*(volatile u8 * )0x44)  // Timer/Counter Register – TCNT0
#define TCCR2	 (*(volatile u8 * )0x45)  // Timer/Counter Control Register – TCCR0

#define	CS20 0
#define	CS21 1
#define	CS22 2
#define	WGM21 3
#define	COM20 4
#define	COM21 5
#define	WGM20 6
#define	FOC2 7

//CS02 , CS01 , CS00   Clock Select 
// WGM00,01  Waveform Generation Mode(TIMER0_NORMAL,	TIMER0_PHASE_PWM,	TIMER0_CTC,	TIMER0_FAST_PWM)
//		COM00 ,	COM01		Compare Match Output Mode


#define TIMSK	 (*(volatile u8 * )0x59)  // Timer/Counter Interrupt Mask Register – TIMSK


#define	TIOE2	6
#define	OCIE2	7

#define OCR2 	 (*(volatile u8 * )0x43) // Output Compare Register – OCR0

#define TIFR	 (*(volatile u8 * )0x58) // Timer/Counter Interrupt Flag Register – TIFR


#define	TOV2	6
#define	OCF2	7



#define TIMER2_NORMAL 		1
#define TIMER2_CTC 			2
#define TIMER2_FAST_PWM 	3
#define TIMER2_PHASE_PWM 	4

#define TIMER2_DIV_BY_1			1
#define TIMER2_DIV_BY_8			5
#define TIMER2_DIV_BY_64		8
#define TIMER2_DIV_BY_256		10
#define TIMER2_DIV_BY_1024		15


#define TIMER2_NO_ACTION	100
#define TIMER2_TOGGLE		12
#define TIMER2_SET			20
#define TIMER2_CLEAR		25


#endif
