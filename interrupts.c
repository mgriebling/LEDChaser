//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     interrupts.c
* \details  Interrupt handler for timer that sequences the LEDs.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "Sequences.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

void interrupt isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */
    
    /* TODO Add High Priority interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if (PIR1bits.TMR2IF) {
        Sequences_Update();     /* Scan LEDs */
        PIR1bits.TMR2IF = 0;    /* Clear Interrupt Flag 1 */
    } else {
        /* Unhandled interrupts */
    }
}
