//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     main.c
* \details  Top-level source code module.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdlib.h>        /* For random() */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "Sequences.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

uint8_t ReadSwitches (void) {
    return (~PORTC) & 0x7;
}

uint8_t main(void)
{
    uint8_t option, i;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    Sequences_SetActive(14);   // LED check
    Sequences_Play(15);
    Sequences_SetActive(15);   // Software version number
    Sequences_Play(5);

    while(1) {
        // Check switches for change
        option = ReadSwitches();
        if (option == 0) {
            // show all the display sequences
            for (i=0; i<13; i++) {
                Sequences_SetActive(i);
                Sequences_Play(20);
                Sequences_SetActive(13);
                Sequences_Play(2);      /* blank */
                option = ReadSwitches();
                if (option != 0) break;
            }
        } else {
            Sequences_SetActive(option);
        }

        // Drive the LEDs
        Sequences_Play(10);
    }
    return 0;
}

