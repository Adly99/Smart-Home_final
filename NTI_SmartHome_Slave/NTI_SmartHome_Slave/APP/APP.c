/*
 * APP.c
 *
 * Created: 3/16/2023 11:31:31 PM
 *  Author: Dell
 */ 

#include "APP.h"

void APP_Init(){
	TIMER0_void_Init();
	TIMER2_void_Init();
	ADC_voidEnable();
	ADC_voidInit();
	GIE_voidEnable();
	LED_INIT();
	DHT22_init(DIO_PORTA,DIO_PIN7);
	lcd_vidInit();
	lcd_vidGotoRowColumn(1,1);
	lcd_vidDisplyStr("Valeo Smart Home!");
	Stepper_init();
	Ultrasonic_init();
	UART_init(9600);
	Stepper_init();
	DcMotor_voidInit();
	while(1){
		if (UART_DataAvailable())
		{
					u8 data=UART_receive_char();
					if (data == 'A')
					{
						break;
					}
		}

	}

}
void APP_Run(){
	TemperatureControlTask();
	LightingControlTask();
	WeatherMonitorTask();
	GarageTask();
}
void WeatherMonitorTask(){
	lcd_vidGotoRowColumn(2,0);
	lcd_vidDisplyStr("Temp:");
	lcd_vidDisplyStr(itoa(DHT22_ReadTemperature(Celsius),DHT_BUFFER,10));
	lcd_vidDisplyStr("C ");
	_delay_ms(100);
	lcd_vidDisplyStr("Humid:");
	lcd_vidDisplyStr(itoa(DHT22_ReadHumidity(),DHT_BUFFER,10));
	lcd_vidDisplyStr("%");
}

void GarageTask(){
	u32 UltrasonicDistance=0;
	static u8 GarageOpen=0;
	trigger();
	UltrasonicDistance=getdistance();
	lcd_vidGotoRowColumn(3,0);
	lcd_vidDisplyStr("Distance:");
	lcd_vidDisplyStr(itoa(getdistance(),DHT_BUFFER,10));
	lcd_vidDisplyStr("cm ");
	if (UltrasonicDistance<20 && GarageOpen == 0)
		{
			Stepper_moveFullStepDeg(FirstStepper,StepperForward,360);
			GarageOpen=1;
		}
	else if(UltrasonicDistance > 20 && GarageOpen == 1)
		{
			Stepper_moveFullStepDeg(FirstStepper,StepperReverse,360);
			GarageOpen=0;
		}
		
}
void TemperatureControlTask(){
		u8 FanSpeed=0;
		Temperature=LM_35_Function();
		if(Temperature>=20 && Temperature<=50){
			FanSpeed=(Temperature-20)*255/30;	
		}
		DcMotor_voidMove(RIGHT,FanSpeed);
}
void LDR(void)
{
	
	ldr=ADC_u16ReadADCInMV();
	

}
void LightingControlTask(){
	LDR_Function(ldr);
}