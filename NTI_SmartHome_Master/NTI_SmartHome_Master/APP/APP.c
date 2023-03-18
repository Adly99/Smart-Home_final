/*
 * APP.c
 *
 * Created: 3/16/2023 4:33:10 PM
 *  Author: Dell
 */
#include "APP.h"

void APP_INIT(void){


	//u8 x;
	keypad_int();
	lcd_vidInit();
	buzzer_init();
	servo_init();
	UART_init(9600);
	
	EXT0_voidCallBack(PersonEntered);
	EXT0_voidInit();
	EXT0_voidEnable();
	
	EEPROM_write(306,0);
	if(EEPROM_read(306)==0)
		FirstPasswordEnter (NewPassword);
		
	PasswordCorrectFlag=check_password (password);
	WrongPasswordCheck(PasswordCorrectFlag);
	DoorEntrance();
	SendConfirmation();	
}

void APP_RUN(void){
	
	PasswordCorrectFlag=check_password (password);
	WrongPasswordCheck(PasswordCorrectFlag);
	DoorEntrance();
	SendConfirmation();	
	/*if(){
		
	}*/
}

void FirstPasswordEnter (u8 *NewPassword)
{
	volatile u8 count=0;
	volatile u8 keypad_number='\0';
	
	
	///////////////////////////////////enter pass
	lcd_vidGotoRowColumn(0,0);
	lcd_vidDisplyStr("Enter New Password");
	lcd_vidGotoRowColumn(1,0);
	lcd_vidDisplyStr("Enter 4 Numbers Only");
	lcd_vidGotoRowColumn(2,8);
	
	while(count!=4)///////////////////////LOOOOP TO take the new pass
	{
		keypad_number=keyad_getnumber();
		_delay_ms(100);
		if(keypad_number==100)
		{
			
		}
		else
		{
			lcd_vidGotoRowColumn(2,8+count);
			_delay_ms(100);
			lcd_vidSendData(keypad_number);
			_delay_ms(100);
			NewPassword[count]=keypad_number;
			count++;
		}
	}
	/////////////////////////////write on the EPROM
	for(u8 i=0;i<4;i++)
	{
		EEPROM_write(300+i,NewPassword[i]);
	}
	flag=1;
	EEPROM_write(304,flag);
	/////////////////////////////////
	
	
	
}

u8 check_password (u8 *pass)
{
	u8 volatile trial=0;
	u8 volatile PasswordCorrectFlag=0;
	u8 volatile keypad_number=100;
	u8 volatile count=0;
	
	while(trial!=3 && PasswordCorrectFlag==0)///////the trial for 3 times and the PasswordCorrectFlag for if it right or wrong
	{
		
		lcd_vidSendCmd(_LCD_CLEAR);
		lcd_vidGotoRowColumn(0,0);
		lcd_vidDisplyStr("Enter Your Password");
		lcd_vidGotoRowColumn(1,8);
		keypad_number=100;
		
		while(count < 4 && PasswordCorrectFlag==0)///////////////////////write the pass using loop for the pass
		{
			keypad_number=keyad_getnumber();
			//_delay_ms(100);
			if(keypad_number==100)
			{
				
			}
			else
			{
				lcd_vidGotoRowColumn(1,8+count);
				_delay_ms(100);
				lcd_vidSendData(keypad_number);
				_delay_ms(100);
				pass[count]=keypad_number;
				count++;
				
			}
		}
		
		PasswordCorrectFlag=1;
		for(u8 i=0; i<4 ;i++)/////////////////////for loop to check if the pass equal the new pass
		{
			if(pass[i]==EEPROM_read(300+i))
			{
				
				PasswordCorrectFlag=1;
			}
			else
			{
				PasswordCorrectFlag=0;
				lcd_vidSendCmd(_LCD_CLEAR);
				lcd_vidGotoRowColumn(0,3);
				lcd_vidDisplyStr("WRONG PASSWORD");
				_delay_ms(1000);
				lcd_vidSendCmd(_LCD_CLEAR);
				_delay_ms(1000);
				break;
			}
		}
		trial++;
		count=0;
	}
	return PasswordCorrectFlag;
	
}

void WrongPasswordCheck(u8 PasswordCorrectFlag)
{
	if(PasswordCorrectFlag==0)
	{
		while(1)
		{
			lcd_vidSendCmd(_LCD_CLEAR);
			lcd_vidGotoRowColumn(0,3);
			lcd_vidDisplyStr("Theft ALARM!!!");
			buzzer_on();
			_delay_ms(5000);
			buzzer_off();
			break;
		}
		PasswordCorrectFlag=check_password(password);
		WrongPasswordCheck(PasswordCorrectFlag);
	}
}

void DoorEntrance(){
		lcd_vidSendCmd(_LCD_CLEAR);
		lcd_vidGotoRowColumn(0,4);
		lcd_vidDisplyStr("Welcome Sir");
		lcd_vidGotoRowColumn(1,3);
		lcd_vidDisplyStr("Please Enter!");
		servo_full_open();
		PersonEnteredFlag=0;
		while(PersonEnteredFlag == 0);
		servo_full_close();
		PersonEnteredFlag = 1;
}

void PersonEntered(){
	PersonEnteredFlag = 1;
}

void SendConfirmation(){
UART_send_char('A');
}