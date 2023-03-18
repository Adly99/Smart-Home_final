
#ifndef _TIMER1_PRIV
#define _TIMER1_PRIV



#define TIMSK	 (*(volatile u8 * )0x59)
#define OCR0 	 (*(volatile u8 * )0x5C)
#define TCCR0	 (*(volatile u8 * )0x53)
#define TCNT0	 (*(volatile u8 * )0x52)
#define TIFR	 (*(volatile u8 * )0x58)

#define DIO_DDRB_REG		(*(volatile u8*)(0x37))
#define TCCR1A				 (*(volatile u8*)(0x4F))
#define TCCR1B				 (*(volatile u8*)(0x4E))

#define  TCNT1              (*(volatile u16*)(0x4C))
#define  OCR1A				(*(volatile u16*)(0x4A))
#define  OCR1B   			(*(volatile u16*)(0x48))

#define   ICR1				(*(volatile u16*)(0x46))



#endif
