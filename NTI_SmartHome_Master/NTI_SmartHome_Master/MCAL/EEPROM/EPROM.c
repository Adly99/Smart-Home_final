/*
 * EPROM.c
 *
 * Created: 3/11/2023 11:10:12 AM
 *  Author: CONNECT
 */ 
#include "EPROM.h"
#include "EPROM_private.h"


void EEPROM_write(u16 Address, u8 Data)
{
	
	while(EECR & (1<<1));

	EEAR = Address;
	EEDR = Data;

	EECR |= (1<<2);
	EECR |= (1<<1);
}

unsigned char EEPROM_read(u16 Address)
{
	while(EECR & (1<<1));

	EEAR = Address;
	EECR |= (1<<0);

	return EEDR;
}
