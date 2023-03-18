/*
 * EPROM.h
 *
 * Created: 3/11/2023 11:10:47 AM
 *  Author: CONNECT
 */ 


#ifndef EPROM_H_
#define EPROM_H_
#include "..\..\LIB\bit_math.h"
#include "..\..\LIB\std_types.h"

void EEPROM_write(u16 Address, u8 Data);
unsigned char EEPROM_read(u16 Address);



#endif /* EPROM_H_ */