/*
 * UART.h
 *
 * Created: 12/12/2022 9:51:19 AM
 *  Author: Dell
 */ 


#ifndef UART_H_
#define UART_H_
//#include "../../Utilities/ATMEGA8_Registers.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

#define UART_DATA_AVAILABLE 1
#define UART_DATA_UNAVAILABLE 0

#define ESC 0x1B

void UART_init(uint16_t baud_rate); // Initiate the UART
void UART_send_char(char data); // Send signed character
char UART_receive_char(); // Receive single character
void UART_Print(char *data); // Send array of characters
void UART_Println(char *data); //Send array of characters with a newline
void UART_recieve_string(); //Receive array of characters
char* UART_Readline();
char* UART_ReadString();
uint8_t UART_DataAvailable();


#endif /* UART_H_ */