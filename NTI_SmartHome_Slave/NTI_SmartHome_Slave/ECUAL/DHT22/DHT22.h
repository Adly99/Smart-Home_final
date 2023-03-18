/*
 * DHT22.h
 *
 * Created: 12/17/2022 5:09:16 PM
 *  Author: Dell
 */ 


#ifndef DHT22_H_
#define DHT22_H_

#define F_CPU 16000000UL
#include "../../MCAL/DIO/dio.h"
#include <avr/io.h>
#include <util/delay.h>
#define Celsius 0
#define Franehait 1

u8 PORT;
u8 PIN;
volatile u8 c,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void DHT22_init(u8 DHT22_PORT,u8 DHT22_PIN);
void Request();
void Response();
u8 Receive_data();
void FETCH_DHT22_DATA();
u8 DHT22_ReadTemperature(u8 TemperatureUnit);
u8 DHT22_ReadHumidity();




#endif /* DHT22_H_ */