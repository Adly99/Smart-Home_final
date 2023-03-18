/*
 * keypad.h
 *
 * Created: 2/18/2023 11:20:15 PM
 *  Author: CONNECT
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "..\..\MCAL\DIO\dio.h"
#include "..\..\MCAL\DIO\dio_types.h"
#include "..\..\LIB\bit_math.h"
#include <util/delay.h>

void keypad_int(void);
u8 keyad_getnumber(void);


#endif /* KEYPAD_H_ */