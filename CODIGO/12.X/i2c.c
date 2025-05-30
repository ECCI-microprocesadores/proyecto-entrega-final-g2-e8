/* i2c.c */
#include "i2c.h"

void I2C_Init_Master(unsigned char brg) {
    TRIS_SCL = 1;
    TRIS_SDA = 1;
    SSP1STAT = brg;               // slew rate control
    SSP1CON1 = 0x28;              // enable MSSP1 in I2C Master mode
    SSP1CON2 = 0x00;
    SSP1ADD  = (_XTAL_FREQ / (4UL * 100000UL)) - 1;  // 100kHz
}

void I2C_Start(void) {
    SSP1CON2bits.SEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
}

void I2C_Stop(void) {
    SSP1CON2bits.PEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
}

void I2C_Restart(void) {
    SSP1CON2bits.RSEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
}

void I2C_Ack(void) {
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
}

void I2C_Nack(void) {
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
}

short I2C_Write(unsigned char data) {
    SSP1BUF = data;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    return SSP1CON2bits.ACKSTAT;
}

unsigned char I2C_Read(void) {
    SSP1CON2bits.RCEN = 1;
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    return SSP1BUF;
}
