#include "main.h"
#include "i2c.h"
#include "lcd_i2c.h"
#include "dht11.h"
#include <stdio.h>

void OSC_Init(void) {
    OSCTUNEbits.PLLEN = 1;         // Enable PLL
    OSCCONbits.IRCF = 0b1110;      // HFINTOSC = 16MHz
    OSCCONbits.SCS  = 0b00;        // System clock = HFINTOSC
    __delay_ms(1);                 // Stabilization delay
}

void main(void) {
    float temp = 0.0f, hum = 0.0f;
    char buf1[20];
    char buf2[20];

    OSC_Init();

    ANSELA = 0x00;
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00; // RD0 y RD1 como d//igital

    TRISD2 = 0; // RD0 como salida (LED temperatura)
    TRISD3 = 0; // RD1 como salida (LED humedad)

    LATD2 = 0;  // Apagar LED al inicio
    LATD3 = 0;

    I2C_Init_Master(I2C_100KHZ);
    Lcd_Init();

    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Iniciando...");
    __delay_ms(1000);
    Lcd_Clear();

    while (1) {
        if (DHT11_Read_Data(&temp, &hum) == 0) {
            sprintf(buf1, "Humedad: %.1f%%", hum);
            sprintf(buf2, "Temp: %.1f C", temp);

            // Condición para encender LED por temperatura > 25°C
            if (temp > 25.0f)
                LATD2 = 1;
            else
                LATD2 = 0;

            // Condición para encender LED por humedad > 40%
            if (hum > 40.0f)
                LATD3 = 1;
            else
                LATD3 = 0;
        } else {
            sprintf(buf1, "Error sensor");
            buf2[0] = '\0';
            LATD2 = 0; // Apagar LEDs si falla el sensor
            LATD3 = 0;
        }

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(buf1);
        Lcd_Set_Cursor(1,2);
        Lcd_Write_String(buf2);

        __delay_ms(500);
    }
}
