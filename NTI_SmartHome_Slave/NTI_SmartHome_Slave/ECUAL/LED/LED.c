/*
 * LED.c
 *
 * Created: 2/17/2023 3:20:36 PM
 *  Author: Dell
 */ 
#include "LED.h"

void LED_INIT(void){
	dio_vidConfigChannel(DIO_PORTB,DIO_PIN7,OUTPUT);
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN4,OUTPUT);
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN5,OUTPUT);
	dio_vidConfigChannel(DIO_PORTA,DIO_PIN6,OUTPUT);
}
void LED_ON(u8 LED_ID){
	switch (LED_ID)
	{
	case 0:(RED == SOURCE)?dio_vidWriteChannel(DIO_PORTB,DIO_PIN7,STD_HIGH):dio_vidWriteChannel(DIO_PORTB,DIO_PIN7,STD_LOW);
		break;
	case 1:(GREEN == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN4,STD_HIGH):dio_vidWriteChannel(DIO_PORTA,DIO_PIN4,STD_LOW);
		break;
	case 2:(BLUE == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN5,STD_HIGH):dio_vidWriteChannel(DIO_PORTA,DIO_PIN5,STD_LOW);
		break;
	case 3:(YELLOW == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN6,STD_HIGH):dio_vidWriteChannel(DIO_PORTA,DIO_PIN6,STD_LOW);
		break;
	}
}
void LED_OFF(u8 LED_ID){
	switch (LED_ID)
	{
		case 0:(RED == SOURCE)?dio_vidWriteChannel(DIO_PORTB,DIO_PIN7,STD_LOW):dio_vidWriteChannel(DIO_PORTB,DIO_PIN7,STD_HIGH);
		break;
		case 1:(GREEN == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN4,STD_LOW):dio_vidWriteChannel(DIO_PORTA,DIO_PIN4,STD_HIGH);
		break;
		case 2:(BLUE == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN5,STD_LOW):dio_vidWriteChannel(DIO_PORTA,DIO_PIN5,STD_HIGH);
		break;
		case 3:(YELLOW == SOURCE)?dio_vidWriteChannel(DIO_PORTA,DIO_PIN6,STD_LOW):dio_vidWriteChannel(DIO_PORTA,DIO_PIN6,STD_HIGH);
		break;
	}
}
void LED_TOGGLE(u8 LED_ID){
		switch (LED_ID)
		{
			case 0:dio_vidFlipChannel(DIO_PORTB,DIO_PIN7);
			break;
			case 1:dio_vidFlipChannel(DIO_PORTA,DIO_PIN4);
			break;
			case 2:dio_vidFlipChannel(DIO_PORTA,DIO_PIN5);
			break;
			case 3:dio_vidFlipChannel(DIO_PORTA,DIO_PIN6);
			break;
		}
}