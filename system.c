//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     system.c
* \details  Oscillator configuration.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>           /* HiTech General Includes */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
#ifdef _PIC16F690_H_
    OSCCONbits.IRCF = 0b110;    // select a 4 MHz oscillator
#else
    OSCCONbits.IRCF = 0b1101;   // select a 4 MHz oscillator
#endif
}
