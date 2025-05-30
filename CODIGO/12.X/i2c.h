/* i2c.h */
#ifndef I2C_H
#define I2C_H

#include <xc.h>
#define _XTAL_FREQ 64000000UL

#define TRIS_SCL TRISCbits.TRISC3   // SCL1 on RC3
#define TRIS_SDA TRISCbits.TRISC4   // SDA1 on RC4

#define I2C_100KHZ 0x80

void I2C_Init_Master(unsigned char brg);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_Ack(void);
void I2C_Nack(void);
unsigned char I2C_Read(void);
short I2C_Write(unsigned char data);

#endif // I2C_H
