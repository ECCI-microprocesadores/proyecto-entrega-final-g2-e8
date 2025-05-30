#include "lcd.h"

void Lcd_Port(char a)
{
    D4 = (a & 1);
    D5 = (a & 2) >> 1;
    D6 = (a & 4) >> 2;
    D7 = (a & 8) >> 3;
}

void Lcd_Cmd(char a)
{
    RS = 0;
    Lcd_Port(a >> 4);
    EN = 1; __delay_ms(2); EN = 0;
    Lcd_Port(a & 0x0F);
    EN = 1; __delay_ms(2); EN = 0;
}

void Lcd_Clear(void)
{
    Lcd_Cmd(0x01);
}

void Lcd_Set_Cursor(char a, char b)
{
    char pos = (a == 1) ? (0x80 + b - 1) : (0xC0 + b - 1);
    Lcd_Cmd(pos);
}

void Lcd_Init(void)
{
    RS_DIR = EN_DIR = D4_DIR = D5_DIR = D6_DIR = D7_DIR = 0;
    __delay_ms(20);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x28);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x06);
    Lcd_Clear();
}

void Lcd_Write_Char(char a)
{
    RS = 1;
    Lcd_Port(a >> 4);
    EN = 1; __delay_us(40); EN = 0;
    Lcd_Port(a & 0x0F);
    EN = 1; __delay_us(40); EN = 0;
}

void Lcd_Write_String(const char *a)
{
    while(*a) Lcd_Write_Char(*a++);
}

void Lcd_Shift_Right(void) { Lcd_Cmd(0x1C); }
void Lcd_Shift_Left(void)  { Lcd_Cmd(0x18); }
void Lcd_Blink(void)       { Lcd_Cmd(0x0F); }
void Lcd_NoBlink(void)     { Lcd_Cmd(0x0C); }
