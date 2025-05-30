/* lcd_i2c.h */
#ifndef LCD_I2C_H
#define LCD_I2C_H

#define ADDRESS_LCD 0x4E


void Lcd_Init(void);
void Lcd_Cmd(unsigned char cmd);

void Lcd_Set_Cursor(char col, char row);
void Lcd_Write_Char(char c);
void Lcd_Write_String(const char *str);
void Lcd_Clear(void);

#endif // LCD_I2C_H
