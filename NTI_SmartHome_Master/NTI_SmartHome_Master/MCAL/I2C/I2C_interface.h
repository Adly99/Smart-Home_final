#ifndef		I2C_INTERFACE_H
#define		I2C_INTERFACE_H

typedef enum
{
  I2C_OK = 0,
  I2C_SC_ERROR,
  I2C_RSC_ERROR,
  I2C_MT_SLA_R_ERROR,
  I2C_MT_SLA_W_ERROR,
  I2C_MT_DATA_ERROR,
  I2C_MR_DATA_ERROR,
  I2C_SR_DATA_ERROR
}I2C_Error_State;

void		I2C_Master_voidInit(void);
void		I2C_Slave_voidInit(u8 I2C_Address);
I2C_Error_State   I2C_Master_enuSendStartCond(void);
I2C_Error_State   I2C_Master_enuSendRepeatedStartCond(void);

I2C_Error_State   I2C_Master_enuSendSlaveAddressWithRead(u8 I2C_Address);
I2C_Error_State   I2C_Master_enuSendSlaveAddressWithWrite(u8 I2C_Address);
I2C_Error_State   I2C_Master_enuSendu8Data(u8 I2C_Data);
I2C_Error_State   I2C_Master_enuReadu8Data(u8* I2C_Data);
void   I2C_Master_enuSendStopCond(void);
I2C_Error_State   I2C_Slave_enuReadu8Data(u8* I2C_Data);

void	I2C_Slave_voidListen(void);

#endif
