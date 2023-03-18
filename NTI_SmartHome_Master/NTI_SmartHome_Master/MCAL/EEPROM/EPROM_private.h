/*
 * EPROM_private.h
 *
 * Created: 3/11/2023 11:11:55 AM
 *  Author: CONNECT
 */ 


#ifndef EPROM_PRIVATE_H_
#define EPROM_PRIVATE_H_

#include "..\..\LIB\bit_math.h"
#include "..\..\LIB\std_types.h"

#define   EEARH  *((volatile u8 *) 0x3F)
#define   EEARL  *((volatile u8 *) 0x3E)
#define   EEAR  *((volatile u16 *) 0x3E)

#define   EEDR   *((volatile u8 *) 0x3D)
#define   EECR   *((volatile u8 *) 0x3C)

#endif /* EPROM_PRIVATE_H_ */