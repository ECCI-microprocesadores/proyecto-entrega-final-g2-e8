/* dht11.h */
#ifndef DHT11_H
#define DHT11_H

#include <xc.h>
#define _XTAL_FREQ 64000000UL

#define DHT11_PIN_PORT  PORTAbits.RA1
#define DHT11_PIN_LAT   LATAbits.LATA1
#define DHT11_PIN_DIR   TRISAbits.TRISA1

void DHT11_Start(void);
void DHT11_Response(void);
int  DHT11_Read_Byte(void);
short DHT11_Read_Data(float *tem, float *hum);

#endif // DHT11_H
