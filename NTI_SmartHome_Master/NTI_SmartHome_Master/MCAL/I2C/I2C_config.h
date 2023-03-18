#ifndef		I2C_CONFIG_H
#define		I2C_CONFIG_H

#ifndef     F_CPU
#define     F_CPU             16000000UL
#endif
/*
The I2C_TWBR_VALUE should be > 10 if in master mode
I2C Freq=(F_CPU)/(16+2T)
*/
#define     I2C_TWBR_VALUE        72
/*
I2C_MSTR_MODE can be: (Master/Slave)
              I2C_SLAVE
              I2C_MASTER
*/
#define     I2C_MSTR_MODE         I2C_MASTER

/*
I2C_ACK_MODE can be: (Master/Slave)
              ENABLE
              DISABLE
*/
#define     I2C_ACK_MODE          ENABLE
/*
I2C_GENERAL_CALL_MODE can be:
              ENABLE
              DISABLE
*/
#define     I2C_GENERAL_CALL_MODE          DISABLE
/*
I2C_PRESCALER can be: (Master/Slave)
              I2C_PRESCALER_1
              I2C_PRESCALER_4
              I2C_PRESCALER_16
              I2C_PRESCALER_64
*/
#define    I2C_PRESCALER          I2C_PRESCALER_1



#endif
