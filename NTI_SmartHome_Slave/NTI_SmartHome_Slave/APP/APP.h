/*
 * APP.h
 *
 * Created: 3/16/2023 11:31:43 PM
 *  Author: Dell
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/DHT22/DHT22.h"
#include "../ECUAL/FAN/DcMotor_int.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/LDR/ldr.h"
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/STEPPER/Stepper.h"
#include "../ECUAL/ULTRASONIC/ULTRASONIC_int.h"
#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/uart.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/TIMER/TIMER0/TIMR0_int.h"
#include "../MCAL/TIMER/TIMER2/TIMER2_int.h"
#include "../ECUAL/STEPPER/Stepper.h"
#include "../ECUAL/LM35/LM35.h"
#include <stdlib.h>

static char DHT_BUFFER[4]="";
u16 ldr;
u16 Temperature;

void LDR(void);
void GarageTask(void);
void WeatherMonitorTask(void);
void TemperatureControlTask(void);
void LightingControlTask(void);

void APP_Init(void);
void APP_Run(void);

#endif /* APP_H_ */