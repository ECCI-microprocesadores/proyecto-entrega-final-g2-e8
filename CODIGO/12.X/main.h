/* main.h */
#ifndef MAIN_H
#define MAIN_H

#include <xc.h>
#include <stdint.h>

// CONFIG1H
#pragma config FOSC   = INTIO67   // Internal oscillator block
#pragma config PLLCFG = OFF       // 4X PLL Disabled
#pragma config PRICLKEN = OFF     // Primary clock can be disabled by software
#pragma config FCMEN  = OFF       // Fail-Safe Clock Monitor disabled
#pragma config IESO   = OFF       // Internal/External Switchover disabled

// CONFIG2L
#pragma config PWRTEN = OFF       // Power-up Timer disabled
#pragma config BOREN  = OFF       // Brown-out Reset disabled
#pragma config BORV   = 190       // Brown-out Reset Voltage (1.90V)

// CONFIG2H
#pragma config WDTEN  = OFF       // Watchdog Timer disabled
#pragma config WDTPS  = 32768     // Watchdog Timer Postscale (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1    // CCP2 on RC1
#pragma config P2BMX  = PORTD2    // ECCP2 B on RD2
#pragma config T3CMX  = PORTC0    // T3CKI on RC0
#pragma config MCLRE  = EXTMCLR   // MCLR pin enabled
#pragma config HFOFST = OFF       // HFINTOSC Fast Start-up disabled
#pragma config PBADEN = OFF       // PORTB<5:0> digital on reset

// CONFIG4L
#pragma config STVREN = OFF       // Stack Overflow/Underflow Reset disabled
#pragma config LVP    = OFF       // Low-Voltage Programming disabled
#pragma config DEBUG  = OFF       // Debugger disabled

#define _XTAL_FREQ 64000000UL     // HFINTOSC 16MHz ×4 PLL = 64MHz

void OSC_Init(void);

#endif // MAIN_H
