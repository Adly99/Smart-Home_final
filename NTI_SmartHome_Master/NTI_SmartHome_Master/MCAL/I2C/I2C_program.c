#include		"Std_Types.h"
#include		"Bit_Math.h"
//#include 		"dio.h"
#include		"I2C_interface.h"
#include		"I2C_private.h"
#include		"I2C_config.h"

void I2C_Master_voidInit(void)
{
	TWBR_REG= I2C_TWBR_VALUE;
	#if 		I2C_PRESCALER == I2C_PRESCALER_1
		CLEAR_BIT(TWSR_REG,TWPS0);
		CLEAR_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_4
		SET_BIT(TWSR_REG,TWPS0);
		CLEAR_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_16
		CLEAR_BIT(TWSR_REG,TWPS0);
		SET_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_64
		SET_BIT(TWSR_REG,TWPS0);
		SET_BIT(TWSR_REG,TWPS1);
	#endif

	#if 		I2C_ACK_MODE == DISABLE
		CLEAR_BIT(TWCR_REG,TWEA);
	#elif 	I2C_ACK_MODE == ENABLE
		SET_BIT(TWCR_REG,TWEA);
	#endif

	#if 		I2C_GENERAL_CALL_MODE == DISABLE
		CLEAR_BIT(TWAR_REG,TWGCE);
	#elif 	I2C_GENERAL_CALL_MODE == ENABLE
		SET_BIT(TWAR_REG,TWGCE);
	#endif

	SET_BIT(TWCR_REG,TWEN);
}

void		I2C_Slave_voidInit(u8 I2C_Address)
{
	TWBR_REG= I2C_TWBR_VALUE;
	#if 		I2C_PRESCALER == I2C_PRESCALER_1
		CLEAR_BIT(TWSR_REG,TWPS0);
		CLEAR_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_4
		SET_BIT(TWSR_REG,TWPS0);
		CLEAR_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_16
		CLEAR_BIT(TWSR_REG,TWPS0);
		SET_BIT(TWSR_REG,TWPS1);
	#elif 	I2C_PRESCALER == I2C_PRESCALER_64
		SET_BIT(TWSR_REG,TWPS0);
		SET_BIT(TWSR_REG,TWPS1);
	#endif

	#if 		I2C_ACK_MODE == DISABLE
		CLEAR_BIT(TWCR_REG,TWEA);
	#elif 	I2C_ACK_MODE == ENABLE
		SET_BIT(TWCR_REG,TWEA);
	#endif

	#if 		I2C_GENERAL_CALL_MODE == DISABLE
		CLEAR_BIT(TWAR_REG,TWGCE);
	#elif 	I2C_GENERAL_CALL_MODE == ENABLE
		SET_BIT(TWAR_REG,TWGCE);
	#endif

	SET_BIT(TWCR_REG,TWEN);
	TWAR_REG=(I2C_Address<<1);
}

I2C_Error_State   I2C_Master_enuSendStartCond(void)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Send the start condition  */
	SET_BIT(TWCR_REG,TWSTA);
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag to confirm transmitting the start conditon */
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_SC_ACK)
	{
		Local_enuError= I2C_SC_ERROR;
	}
	return Local_enuError;
}


I2C_Error_State   I2C_Master_enuSendRepeatedStartCond(void)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Send the start condition  */
	SET_BIT(TWCR_REG,TWSTA);
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag to confirm transmitting the start conditon */
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_RSC_ACK)
	{
		Local_enuError= I2C_RSC_ERROR;
	}
	return Local_enuError;
}

I2C_Error_State   I2C_Master_enuSendSlaveAddressWithRead(u8 I2C_Address)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Put Address to TWDR_REG  */
	TWDR_REG=(I2C_Address<<1);
	/*		Read Operation  */
	SET_BIT(TWDR_REG,0);
	/*		CLR the start condition  */
	CLEAR_BIT(TWCR_REG,TWSTA);
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag */
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_MT_SLA_R_ACK)
	{
		Local_enuError= I2C_MT_SLA_R_ERROR;
	}
	return Local_enuError;
}

I2C_Error_State   I2C_Master_enuSendSlaveAddressWithWrite(u8 I2C_Address)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Put Address to TWDR_REG  */
	TWDR_REG=(I2C_Address<<1);
	/*		Write Operation  */
	CLEAR_BIT(TWDR_REG,0);
	/*		CLR the start condition  */
	CLEAR_BIT(TWCR_REG,TWSTA);
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag*/
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_MT_SLA_W_ACK)
	{
		Local_enuError= I2C_MT_SLA_W_ERROR;
	}
	return Local_enuError;
}

I2C_Error_State   I2C_Master_enuSendu8Data(u8 I2C_Data)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Put Data to TWDR_REG  */
	TWDR_REG=I2C_Data;
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag*/
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_MT_DATA_ACK)
	{
		Local_enuError= I2C_MT_DATA_ERROR;
	}
	return Local_enuError;
}


I2C_Error_State   I2C_Master_enuReadu8Data(u8* I2C_Data)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag*/
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_MR_DATA_ACK)
	{
		Local_enuError= I2C_MR_DATA_ERROR;
	}
	else
	{
		*I2C_Data =TWDR_REG;
	}
	return Local_enuError;
}


void   I2C_Master_enuSendStopCond(void)
{

	/*		Send the stop condition  */
	SET_BIT(TWCR_REG,TWSTO);
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
}

void	I2C_Slave_voidListen(void)
{
	
	/*		Polling on the flag*/
	while (!(TWCR_REG &  (1<<TWINT)));
	
}
I2C_Error_State   I2C_Slave_enuReadu8Data(u8* I2C_Data)
{
	I2C_Error_State Local_enuError= I2C_OK;
	/*		Turn off the flag  */
	SET_BIT(TWCR_REG,TWINT);
	/*		Polling on the flag*/
	while (!(TWCR_REG &  (1<<TWINT)));
	if ((TWSR_REG & 0xF8)!=I2C_SR_DATA_ACK)
	{
		Local_enuError= I2C_SR_DATA_ERROR;
	}
	else
	{
		*I2C_Data =TWDR_REG;
	}
	return Local_enuError;
}
