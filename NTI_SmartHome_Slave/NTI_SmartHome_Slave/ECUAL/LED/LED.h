/*
 * LED.h
 *
 * Created: 2/17/2023 3:20:22 PM
 *  Author: Dell
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"
#include "LEDcfg.h"

#define RED_LED 0
#define GREEN_LED 1
#define BLUE_LED 2
#define YELLOW_LED 3

void LED_INIT(void);
void LED_ON(u8 LED_ID);
void LED_OFF(u8 LED_ID);
void LED_TOGGLE(u8 LED_ID);



#endif /* LED_H_ */