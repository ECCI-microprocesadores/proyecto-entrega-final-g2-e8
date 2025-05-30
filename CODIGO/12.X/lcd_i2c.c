/* lcd_i2c.c */
#define _XTAL_FREQ 64000000UL
#include <xc.h>
#include "i2c.h"
#include "lcd_i2c.h"

void Lcd_Init(void) {
    __delay_ms(20);
    Lcd_Cmd(0x33);
    Lcd_Cmd(0x32);
    Lcd_Cmd(0x28);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x06);
    Lcd_Cmd(0x01);
    __delay_ms(3);
}

void Lcd_Cmd(unsigned char cmd) {
    unsigned char hi = cmd & 0xF0;
    unsigned char lo = (cmd << 4) & 0xF0;
    I2C_Start();
    I2C_Write(ADDRESS_LCD);
    I2C_Write(hi | 0x0C);
    I2C_Write(hi | 0x08);
    I2C_Write(lo | 0x0C);
    I2C_Write(lo | 0x08);
    I2C_Stop();
}

void Lcd_Set_Cursor(char col, char row) {
    unsigned char addr;
    switch (row) {
        case 1: addr = 0x00; break;
        case 2: addr = 0x40; break;
        case 3: addr = 0x14; break;
        case 4: addr = 0x54; break;
        default: addr = 0x00;
    }
    addr += col - 1;
    Lcd_Cmd(0x80 | addr);
}

void Lcd_Write_Char(char c) {
    unsigned char hi = c & 0xF0;
    unsigned char lo = (c << 4) & 0xF0;
    I2C_Start();
    I2C_Write(ADDRESS_LCD);
    I2C_Write(hi | 0x0D);
    I2C_Write(hi | 0x09);
    I2C_Write(lo | 0x0D);
    I2C_Write(lo | 0x09);
    I2C_Stop();
}

void Lcd_Write_String(const char *str) {
    while (*str) Lcd_Write_Char(*str++);
}

void Lcd_Clear(void) {
    Lcd_Cmd(0x01);
    __delay_ms(2);
}
