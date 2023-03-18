/*
 * NTI_SmartHome_Slave.c
 *
 * Created: 3/16/2023 11:26:31 PM
 * Author : Dell
 */ 

#include <avr/io.h>
#include "APP/APP.h"

int main(void)
{
    APP_Init();
    while (1) 
    {
		APP_Run();
    }
}

