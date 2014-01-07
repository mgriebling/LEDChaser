//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     user.c
* \details  Port and input/output bit set-up.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"
#include "LEDs.h"
#include "Sequences.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
#ifdef _PIC16F690_H_
    ANSEL = 0;
    ANSELH = 0;
#else
    ANSELA = 0;     // No analog functions needed
    ANSELB = 0;
    ANSELC = 0;
#endif

    /* Initialize peripherals */
    TRISA = 0xFF;      // All port pins are inputs initially
    TRISB = 0xFF;
    TRISC = 0xFF;

    LEDs_Init();
    Sequences_Init();

    /* Enable interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

