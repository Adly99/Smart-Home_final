/*
 * keypad.c
 *
 * Created: 2/18/2023 11:19:17 PM
 *  Author: CONNECT
 */ 
#include "keypad.h"



u8 arr[4][4]=
             {
			  {'1','2','3','+'},
			  {'4','5','6','-'},
			  {'7','8','9','*'},  	 
			  {'#','0','=','/'}  
			 };
			 
			 
			 
void keypad_int(void)
{
	//////////////////////////////column
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN7,INPUT);
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN6,INPUT);
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN5,INPUT);
	dio_vidConfigChannel(DIO_PORTD,DIO_PIN3,INPUT);

	
	
	//////////////////////////////row
	dio_vidConfigChannel(DIO_PORTC,DIO_PIN5,OUTPUT);
	dio_vidConfigChannel(DIO_PORTC,DIO_PIN4,OUTPUT);
	dio_vidConfigChannel(DIO_PORTC,DIO_PIN3,OUTPUT);
	dio_vidConfigChannel(DIO_PORTC,DIO_PIN2,OUTPUT);
	
	dio_vidWriteChannel(DIO_PORTC,DIO_PIN5,STD_HIGH);
	dio_vidWriteChannel(DIO_PORTC,DIO_PIN4,STD_HIGH);
	dio_vidWriteChannel(DIO_PORTC,DIO_PIN3,STD_HIGH);
	dio_vidWriteChannel(DIO_PORTC,DIO_PIN2,STD_HIGH);
	
	
}
u8 keyad_getnumber(void)
{
	u8 y=5;
	u8 x=0,z=100;
	u8 col,row;
	for( row=0;row<4;row++)
	{
		dio_vidWriteChannel(DIO_PORTC,y,STD_LOW);
		for( col=0;col<3;col++)
		{
			x=dio_dioLevelReadChannel(DIO_PORTD,7-col);
			if(x==0)
			{
				//z=row*4+col;
				while(x==0)
				{
					x=dio_dioLevelReadChannel(DIO_PORTD,7-col);
				}
				return arr[row][col];
				_delay_ms(2);
			}
			
			
		}
		dio_vidWriteChannel(DIO_PORTC,y,STD_HIGH);
		y--;
		
	}
//////////////////////////////////////////////
y=5;
for( row=0;row<4;row++)
{
dio_vidWriteChannel(DIO_PORTC,y,STD_LOW);
    
    
	    x=dio_dioLevelReadChannel(DIO_PORTD,3);
	    if(x==0)
	      {
	      //	z=row*4+col;
	     	while(x==0)
	     	{
			x=dio_dioLevelReadChannel(DIO_PORTD,3);
	     	}
		    _delay_ms(2);
			return arr[row][3];
	     }
	
dio_vidWriteChannel(DIO_PORTC,y,STD_HIGH);	
y--;
}

////////////////////////////////////////////	
	return 100;
}