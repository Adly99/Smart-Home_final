/*
 * DHT22.c
 *
 * Created: 12/17/2022 5:09:04 PM
 *  Author: Dell
 */ 
#include "DHT22.h"
void DHT22_init(u8 DHT22_PORT,u8 DHT22_PIN){
	PORT=DHT22_PORT;
	PIN=DHT22_PIN;
}
void Request()				/* Micro controller send start pulse/request */
{
	dio_vidConfigChannel(PORT,PIN,OUTPUT);
	dio_vidWriteChannel(PORT,PIN,STD_LOW);	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	dio_vidWriteChannel(PORT,PIN,STD_HIGH);	/* set to high pin */
}
void Response()				/* receive response from DHT22 */
{
	dio_vidConfigChannel(PORT,PIN,INPUT);
	while(dio_dioLevelReadChannel(PORT,PIN));
	while(dio_dioLevelReadChannel(PORT,PIN)==0);
	while(dio_dioLevelReadChannel(PORT,PIN));
}
u8 Receive_data()			/* receive data */
{
	for (int q=0; q<8; q++)
	{
		while(dio_dioLevelReadChannel(PORT,PIN) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(dio_dioLevelReadChannel(PORT,PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(dio_dioLevelReadChannel(PORT,PIN));
	}
	return c;
}
void FETCH_DHT22_DATA(){
	Request();
	Response();
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
}
u8 DHT22_ReadTemperature(u8 TemperatureUnit){
	
	FETCH_DHT22_DATA();
	int Temperature=((I_Temp*256+D_Temp)/10.0);
	return Temperature;
}
u8 DHT22_ReadHumidity(){
	FETCH_DHT22_DATA();
	int Humidity=((I_RH*256+D_RH)/10.0);
	return Humidity;
}