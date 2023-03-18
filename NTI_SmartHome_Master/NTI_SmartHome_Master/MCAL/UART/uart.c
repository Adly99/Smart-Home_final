/*
 * UART.c
 *
 * Created: 12/12/2022 9:51:06 AM
 *  Author: Dell
 */ 
#include "uart.h"
char SerialBuffer[128]={ESC};
char *SerialBufferPointer=SerialBuffer;
char *SerialBufferReader=SerialBuffer;

char SerialTransmitBuffer[128]={ESC};
char *SerialTransmitBufferPointer=SerialTransmitBuffer;
char *SerialTransmitBufferReader=SerialTransmitBuffer;
//uint8_t SerialBufferReader=0;
uint16_t UBRR_Value; // Variable to store the calculations needed to set speed
void UART_init(uint16_t baud_rate)
{
	uint16_t UBRR_Value = lrint ( (F_CPU / (16L * baud_rate) ) -1);
	UBRRL = (uint8_t) UBRR_Value;
	UBRRH = (uint8_t) (UBRR_Value >> 8);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	sei();
	UCSRB |=(1<<RXCIE);
	UCSRB |=(1<<TXCIE);
}
void UART_send_char(char data)
{
	while( ! (UCSRA & (1<<UDRE) ) );
	UDR = data;
}
/*char UART_receive_char()
{
	char ReceievedCharacter='\0';
	if( (UCSRA & (1 << RXC) ) ){
		ReceievedCharacter=UDR;
	}
return ReceievedCharacter;
}*/
uint8_t UART_DataAvailable(){
	uint8_t DataAvailable= UART_DATA_UNAVAILABLE;
	char* DataAvailablePointer=SerialBufferReader;//-((SerialBufferPointer!=SerialBuffer)*sizeof(char))
	if (*(DataAvailablePointer)!=ESC)
	{
		DataAvailable=UART_DATA_AVAILABLE;
	}
	return DataAvailable;
}
char UART_receive_char(){
	//char ReceivedChar;
	char ReceivedCharPointer=ESC;
	if (UART_DataAvailable())
	{
	ReceivedCharPointer=*(SerialBufferReader);
	*(SerialBufferReader)=ESC;
	SerialBufferReader++;
	if(SerialBufferReader==SerialBuffer+128){
		SerialBufferReader=SerialBuffer;
	}
	}
	return ReceivedCharPointer;	
}
void UART_Print(char *data)
{
	while(*data > 0){
		*SerialTransmitBufferPointer=*data++;
		SerialTransmitBufferPointer++;
		if(SerialTransmitBufferPointer==SerialTransmitBuffer+128){
			SerialTransmitBufferPointer=SerialTransmitBuffer;
			}
	}
	*SerialTransmitBufferPointer=ESC;
	SerialTransmitBufferPointer++;
	if(SerialTransmitBufferPointer==SerialTransmitBuffer+128){
		SerialTransmitBufferPointer=SerialTransmitBuffer;
	}
	UART_send_char(*SerialTransmitBufferReader);
	
	/*while(*data > 0)
	UART_send_char(*data++);
	UART_send_char('\0');*/
}
void UART_Println(char *data)
{
	while(*data > 0)
	UART_send_char(*data++);
	UART_send_char('\n');
	UART_send_char('\0');
}
char* UART_ReadString(){
	uint8_t UART_StringIndex=0;
	char UART_String[64]={};
	char *PtrToString=UART_String;
		if(*(SerialBufferReader)==ESC){
			return "";
		}
	while (*(SerialBufferReader) != ESC)
	{
		if(*(SerialBufferReader) != '\0'){
			UART_String[UART_StringIndex]=*(SerialBufferReader);
			UART_StringIndex++;
			*(SerialBufferReader)=ESC;
			SerialBufferReader++;
			if(SerialBufferReader==SerialBuffer+128){
				SerialBufferReader=SerialBuffer;
			}
		}
		else{
			UART_String[UART_StringIndex]=*(SerialBufferReader);
			UART_StringIndex++;
			*(SerialBufferReader)=ESC;
			SerialBufferReader++;
			if(SerialBufferReader==SerialBuffer+128){
				SerialBufferReader=SerialBuffer;
			}
			break;
		}
	}
	return PtrToString;
}
char* UART_Readline(){
	uint8_t UART_LineIndex=0;
	char UART_Line[64]={};
	char *PtrToLine=UART_Line;
	if(*(SerialBufferReader)==ESC){
		return "\n";
	}
	if(*(SerialBufferReader)=='\0'){
		*(SerialBufferReader)=ESC;
		SerialBufferReader++;
		if(SerialBufferReader==SerialBuffer+128){
			SerialBufferReader=SerialBuffer;
		}
		return "\n";
		}
	while (*(SerialBufferReader) != ESC)
	{
		if (*(SerialBufferReader) != '\n')
		{
			UART_Line[UART_LineIndex]=*(SerialBufferReader);
			UART_LineIndex++;
			*(SerialBufferReader)=ESC;
			SerialBufferReader++;
			if(SerialBufferReader==SerialBuffer+128){
				SerialBufferReader=SerialBuffer;
			}
		}
		else{
			UART_Line[UART_LineIndex]=*(SerialBufferReader);
			UART_LineIndex++;
			UART_Line[UART_LineIndex]='\0';
			*(SerialBufferReader)=ESC;
			SerialBufferReader++;
			if(SerialBufferReader==SerialBuffer+128){
				SerialBufferReader=SerialBuffer;
			}
			break;
		}
	}
	return PtrToLine;	
}
ISR(USART_RXC_vect){
	*(SerialBufferPointer++)=UDR;
	if(SerialBufferPointer==SerialBuffer+128){
		SerialBufferPointer=SerialBuffer;
	}
}
ISR(USART_TXC_vect){
	SerialTransmitBufferReader++;
	if (SerialTransmitBufferReader==SerialTransmitBuffer+128)
	{
		SerialTransmitBufferReader=SerialTransmitBuffer;
	}
	if (*SerialTransmitBufferReader==ESC)
	{
		SerialTransmitBufferReader++;
	}
	else{
		UART_send_char(*SerialTransmitBufferReader);	
	}
}