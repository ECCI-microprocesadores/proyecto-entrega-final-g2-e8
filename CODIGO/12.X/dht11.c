/* dht11.c */
#include "dht11.h"

void DHT11_Start(void) {
    DHT11_PIN_DIR = 0;
    DHT11_PIN_LAT = 0;
    __delay_ms(20);
    DHT11_PIN_LAT = 1;
    __delay_us(30);
    DHT11_PIN_DIR = 1;
}

void DHT11_Response(void) {
    while (DHT11_PIN_PORT == 1);
    while (DHT11_PIN_PORT == 0);
    while (DHT11_PIN_PORT == 1);
}

int DHT11_Read_Byte(void) {
    int i, data = 0;
    for (i = 0; i < 8; i++) {
        while (DHT11_PIN_PORT == 0);
        __delay_us(30);
        data <<= 1;
        if (DHT11_PIN_PORT == 1) data |= 1;
        while (DHT11_PIN_PORT == 1);
    }
    return data;
}

short DHT11_Read_Data(float *tem, float *hum) {
    int info[5];
    DHT11_Start();
    DHT11_Response();
    for (int i = 0; i < 5; i++) info[i] = DHT11_Read_Byte();
    *hum = info[0] + info[1] / 10.0f;
    *tem = info[2] + info[3] / 10.0f;
    int sum = info[0] + info[1] + info[2] + info[3];
    return ((sum & 0xFF) == info[4]) ? 0 : -1;
}
