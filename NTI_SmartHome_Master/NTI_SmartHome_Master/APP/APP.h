/*
 * APP.h
 *
 * Created: 3/16/2023 4:33:00 PM
 *  Author: Dell
 */ 


#ifndef APP_H_
#define APP_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "..\LIB\bit_math.h"
#include "..\LIB\std_types.h"
#include "..\ECUAL\LCD\lcd.h"
#include "..\MCAL\DIO\dio.h"
//#include "..\MCAL\ADC\ADC_int.h"
#include "..\MCAL\EEPROM\EPROM.h"
#include "..\ECUAL\KEYPAD\keypad.h"
//#include "..\APP\passward\pass.h"
//#include "..\HAL\LED\led.h"
#include "..\ECUAL\BUZZER/buzzer.h"
#include "..\MCAL\INTERRUPT\EXT0\EXTI0_int.h"
#include "../ECUAL/SERVO/servo.h"
#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/UART/uart.h"

static volatile u8 password[4]={0};
static volatile u8 NewPassword[4];
static volatile u8 flag =0;
static volatile u8 PasswordCorrectFlag=0;
static volatile u8 PersonEnteredFlag=0;
static I2C_Error_State Error = I2C_OK;

void APP_INIT(void);
void APP_RUN(void);

void FirstPasswordEnter (u8 *NewPassword);
u8 check_password (u8 *pass);
void WrongPasswordCheck(u8 PasswordCorrectFlag);
void DoorEntrance(void);
void PersonEntered(void);
void SendConfirmation(void);

#endif /* APP_H_ */