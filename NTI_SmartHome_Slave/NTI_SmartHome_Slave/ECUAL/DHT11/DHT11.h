/*
 * DHT11.h
 *
 * Created: 12/17/2022 5:09:16 PM
 *  Author: Dell
 */ 


#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU 16000000UL
#include "../../MCAL/DIO/dio.h"
#include <avr/io.h>
#include <util/delay.h>
#define Celsius 0
#define Franehait 1

u8 PORT;
u8 PIN;
volatile u8 c,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void DHT11_init(u8 DHT11_PORT,u8 DHT11_PIN);
void Request();
void Response();
u8 Receive_data();
void FETCH_DHT11_DATA();
u8 DHT11_ReadTemperature(u8 TemperatureUnit);
u8 DHT11_ReadHumidity();




#endif /* DHT11_H_ */