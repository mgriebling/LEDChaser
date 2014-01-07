//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     LEDs.c
* \details  Multiplexed LED driver code.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

#include "LEDs.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include <htc.h>           /* Global Header File */

#define LED_MASK1   (0x34)
#define LED_MASK2   (0xF8)

// LED drive definitions for LED1 to LED32
const uint8_t LEDs[] = {0x00, 0x80, 0x01, 0x81, 0x02, 0x82, 0x03, 0x83,     /* row 1 all columns */
                        0x20, 0xA0, 0x21, 0xA1, 0x22, 0xA2, 0x23, 0xA3,     /* row 3 all columns */
                        0x10, 0x90, 0x11, 0x91, 0x12, 0x92, 0x13, 0x93,     /* row 2 all columns */
                        0x30, 0xB0, 0x31, 0xB1, 0x32, 0xB2, 0x33, 0xB3      /* row 4 all columns */
                        };

#ifdef _PIC16F690_H_
#define ROW0    PORTAbits.RA5
#define ROW1    PORTAbits.RA4
#define ROW2    PORTAbits.RA2
#define ROW3    PORTCbits.RC5
#define COL0    PORTCbits.RC4
#define COL1    PORTCbits.RC3
#define COL2    PORTCbits.RC6
#define COL3    PORTCbits.RC7
#else
#define ROW0    LATAbits.LATA5
#define ROW1    LATAbits.LATA4
#define ROW2    LATAbits.LATA2
#define ROW3    LATCbits.LATC5
#define COL0    LATCbits.LATC4
#define COL1    LATCbits.LATC3
#define COL2    LATCbits.LATC6
#define COL3    LATCbits.LATC7
#endif

static inline void DriveRow (uint8_t row, uint8_t level) {
    switch (row) {
        case 0:
            ROW0 = level;
            TRISAbits.TRISA5 = 0;
            break;
        case 1:
            ROW1 = level;
            TRISAbits.TRISA4 = 0;
            break;
        case 2:
            ROW2 = level;
            TRISAbits.TRISA2 = 0;
            break;
        default:
            ROW3 = level;
            TRISCbits.TRISC5 = 0;
            break;
    }
}

static inline void DriveCol (uint8_t col, uint8_t level) {
    if (level == 0) level = 1;
    else level = 0;
    switch (col) {
        case 0:
            COL0 = level;
            TRISCbits.TRISC4 = 0;
            break;
        case 1:
            COL1 = level;
            TRISCbits.TRISC3 = 0;
            break;
        case 2:
            COL2 = level;
            TRISCbits.TRISC6 = 0;
            break;
        default:
            COL3 = level;
            TRISCbits.TRISC7 = 0;
            break;
    }
}

void LEDs_TurnOn (uint8_t led) {
    uint8_t leds, drive;

    LEDs_AllOff();
    if (led < sizeof(LEDs)) {
        leds = LEDs[led];
        if (leds & 0x80) drive = 1;
        else drive = 0;
        DriveRow((leds>>4) & 0x7, drive);
        DriveCol(leds & 0x7, drive);
    }
}

void LEDs_AllOff (void) {
    TRISA |= LED_MASK1;         // set to inputs
    TRISC |= LED_MASK2;

    // Clear the drives
#ifdef _PIC16F690_H_
    PORTA &= ~LED_MASK1;
    PORTC &= ~LED_MASK2;
#else
    LATA &= ~LED_MASK1;
    LATC &= ~LED_MASK2;
#endif
}

void LEDs_Init (void) {
    LEDs_AllOff();
}
