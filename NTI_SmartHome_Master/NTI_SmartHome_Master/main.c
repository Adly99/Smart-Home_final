/*
 * NTI_SmartHome_Master.c
 *
 * Created: 3/16/2023 4:28:39 PM
 * Author : Dell
 */ 

#include <avr/io.h>
#include "APP/APP.h"

int main(void)
{
    APP_INIT();
    while (1) 
    {
		APP_RUN();
    }
}

