//************************************************************************************
//
// This source is Copyright (c) 2014 by Computer Inspirations.  All rights reserved.
// You are permitted to modify and use this code for personal use only.
//
// There is no guarantee that this code will work in your application.
//
//************************************************************************************
/**
* \file     Sequences.c
* \details  Predefined animation sequences and sequence driver to run the animation.
* \author   Michael Griebling
* \date     7 Jan 2014
*/
//************************************************************************************

#include <htc.h>           /* Global Header File */

#include "Sequences.h"
#include "LEDs.h"
#include "system.h"

/* Sequences to play.  Note: First byte is the mode defined as:
 *
 * 1 - Single LED, 2 - Two LEDs, 3 - Three LEDs, ... 32 - All LEDs.
 * Second byte is the time delay each group of LEDs is held on.
 * The time delay can be set to values from 1 - 255 with corresponding
 * times of 8 mS to 2.04 seconds.  A value of zero will use whatever
 * global time delay (1 mS - 65 Secs) has been set for this module.
 *
 * Following bytes represent the LED that is to be lit with
 * valid values from 0 (LED1) to 31 (LED32).  Values greater
 * than 31 can be used to turn off the LED for a number of
 * animation steps.
 */
const uint8_t Random[] = {
        4,      /* Play with four LEDs */
        24,     /* 12 * 8 = 96 mS */
        4, 1, 9, 15, 3, 25, 8, 27, 12, 26, 14, 11, 6, 31, 13, 2,
        20, 17, 18, 23, 10, 24, 16, 19, 22, 29, 7, 21, 5, 30, 0, 28,
        22, 0, 14, 5, 19, 6, 15, 20, 26, 25, 23, 9, 4, 10, 27, 18,
        21, 30, 11, 3, 29, 16, 24, 13, 2, 17, 12, 31, 8, 1, 28, 7
    };

const uint8_t Sparks[] = {
        1,      /* Play with one LED */
        0,      /* Use the default time delay */
        19, 23, 28, 9, 17, 22, 3, 20, 24, 10, 16, 2, 0, 12, 29, 27, 31,
        4, 13, 26, 8, 6, 21, 30, 5, 18, 15, 1, 11, 7, 25, 14, 23, 14,
        1, 19, 30, 25, 16, 21, 0, 28, 22, 13, 29, 9, 5, 6, 7, 26, 2,
        10, 15, 4, 24, 3, 12, 31, 8, 18, 17, 27, 20, 11
    };

const uint8_t Scan[] = {
        1,  /* Play with one LED */
        4,  /* Use the default time delay */
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31,
        30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16,
        15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    };

const uint8_t ScanOut[] = {
        2,  /* Play with two LEDs */
        10, /* 80 mS */
        15, 16, 14, 17, 13, 18, 12, 19, 11, 20, 10, 21, 9, 22,
        8, 23, 7, 24, 6, 25, 5, 26, 4, 27, 3, 28, 2, 29, 1, 30, 0, 31
    };

const uint8_t DoubleScan[] = {
        2,  /* Play with two LEDs */
        6,  /* 48 mS */
        15, 16, 14, 17, 13, 18, 12, 19, 11, 20, 10, 21, 9, 22,
        8, 23, 7, 24, 6, 25, 5, 26, 4, 27, 3, 28, 2, 29, 1, 30,
        0, 31, 1, 30, 2, 29, 3, 28, 4, 27, 5, 26, 6, 25, 7, 24,
        8, 23, 9, 22, 10, 21, 11, 20, 12, 19, 13, 18, 14, 17
    };

const uint8_t QuadScan[] = {
        4,  /* Play with four LEDs */
        12,  /* 96 mS */
        7, 8, 23, 24, 6, 9, 22, 25, 5, 10, 21, 26, 4, 11, 20, 27,
        3, 12, 19, 28, 2, 13, 18, 29, 1, 14, 17, 30, 0, 15, 16, 31,
        1, 14, 17, 30, 2, 13, 18, 29, 3, 12, 19, 28, 4, 11, 20, 27,
        5, 10, 21, 26, 6, 9, 22, 25
    };

const uint8_t ScanTarget[] = {
        1,  /* Play with one LED */
        5,  /* Use the default time delay */
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
        30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
        2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3,
        4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,
        5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
        26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,
        6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
        25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,
        7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7,
        8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
       23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8,
       9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
       22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,
       10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
       21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10,
       11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
       20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
       12, 13, 14, 15, 16, 17, 18, 19, 20,
       19, 18, 17, 16, 15, 14, 13, 12,
       13, 14, 15, 16, 17, 18, 19,
       18, 17, 16, 15, 14, 13,
       14, 15, 16, 17, 18,
       17, 16, 15, 14,
       15, 16, 17,
       16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15, 16, 15
    };

const uint8_t Runway[] = {
        1,      /* Play with one LED */
        12,     /* 12 * 8 = 96 mS */
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31
    };

const uint8_t Target[] = {
        2,      /* Play with two LEDs */
        6,      /* Use the default time delay */
        0, 31, 1, 30, 2, 29, 3, 28, 4, 27, 5, 26, 6, 25, 7, 24,
        8, 23, 9, 22, 10, 21, 11, 20, 12, 19, 13, 18, 14, 17, 15, 16
    };

const uint8_t Snow[] = {
        8,      /* Play with eight LEDs */
        38,     /* 38 * 8 = 304 mS */
        0, 32, 32, 32, 32, 32, 32, 32,
        1, 32, 32, 32, 32, 32, 32, 32,
        2, 32, 32, 32, 32, 32, 32, 32,
        3, 32, 32, 32, 32, 32, 32, 32,
        4,  0, 32, 32, 32, 32, 32, 32,
        5,  1, 32, 32, 32, 32, 32, 32,
        6,  2,  0, 32, 32, 32, 32, 32,
        7,  3,  0, 32, 32, 32, 32, 32,
        8,  4,  1, 32, 32, 32, 32, 32,
        9,  5,  1, 32, 32, 32, 32, 32,
       10,  6,  2, 32, 32, 32, 32, 32,
       11,  7,  2, 32, 32, 32, 32, 32,
       12,  8,  3, 32, 32, 32, 32, 32,
       13,  9,  3, 32, 32, 32, 32, 32,
       14, 10,  4, 32, 32, 32, 32, 32,
       15, 11,  4,  0, 32, 32, 32, 32,
       16, 12,  5,  2, 32, 32, 32, 32,
       17, 13,  5,  4, 32, 32, 32, 32,
       18, 14,  6,  6, 32, 32, 32, 32,
       19, 15,  6,  8, 32, 32, 32, 32,
       20, 16,  7, 10, 32, 32, 32, 32,
       21, 17,  7, 12, 32, 32, 32, 32,
       22, 18,  8, 14, 32, 32, 32, 32,
       23, 19,  8, 16,  0, 32, 32, 32,
       24, 20,  9, 18,  1, 32, 32, 32,
       25, 21,  9, 20,  2, 32, 32, 32,
       26, 22, 10, 22,  3, 32, 32, 32,
       27, 23, 10, 24,  4, 32, 32, 32,
       28, 24, 11, 26,  5, 32, 32, 32,
       29, 25, 11, 28,  6, 32,  0, 32,
       30, 26, 12, 30,  7, 32,  1, 32,
       31, 27, 12, 30,  8, 32,  2, 32,
       31, 28, 13, 30,  9,  0,  3, 32,
       31, 29, 13, 30, 10,  2,  4, 32,
       31, 29, 14, 30, 11,  4,  5,  0,
       31, 29, 14, 30, 12,  6,  6,  3,
       31, 29, 15, 30, 13,  8,  7,  6,
       31, 29, 15, 30, 14,  9,  8,  9,
       31, 29, 16, 30, 15, 10,  9, 12,
       31, 29, 16, 30, 16, 12, 10, 15,
       31, 29, 17, 30, 17, 14, 11, 18,
       31, 29, 17, 30, 18, 16, 12, 21,
       31, 29, 18, 30, 19, 18, 13, 24,
       31, 29, 18, 30, 20, 20, 14, 27,
       31, 29, 19, 30, 21, 22, 15, 28,
       31, 29, 19, 30, 22, 24, 16, 28,
       31, 29, 20, 30, 23, 26, 17, 28,
       31, 29, 20, 30, 24, 27, 18, 28,
       31, 29, 21, 30, 25, 27, 19, 28,
       31, 29, 21, 30, 26, 27, 20, 28,
       31, 29, 22, 30, 26, 27, 21, 28,
       31, 29, 22, 30, 26, 27, 22, 28,
       31, 29, 23, 30, 26, 27, 23, 28,
       31, 29, 23, 30, 26, 27, 24, 28,
       31, 29, 24, 30, 26, 27, 25, 28
    };

const uint8_t Broadway[] = {
        8,      /* Play with eight LEDs */
        31,     /* 31 * 8 = 248 mS */
        0,  4,  8, 12, 16, 20, 24, 28,
        1,  5,  9, 13, 17, 21, 25, 29,
        2,  6, 10, 14, 18, 22, 26, 30,
        3,  7, 11, 15, 19, 23, 27, 31
    };

const uint8_t Blank[] = {
        1,
        32,     /* 32 * 8 = 256 mS */
        32, 32
};

const uint8_t Check[] = {
        32,
        32     /* 32 * 8 = 256 mS */
};

uint8_t DisplayBuffer[32*2+2];     // shared Clock, Counter, & Check display buffer
//        /* Buffer 1 */
//        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//
//        /* Buffer 2 */
//        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
//        0,  1,  2, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 32, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 32, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 32, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 32, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 32, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 32, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 32, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 32, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32,
//        0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
//
//};

const uint8_t Version[] = {
        2,
        250,     /* 2000 mS */
        0, 1
};

const uint8_t Counter[] = {
        /* This is an example of a dynamically updated LED pattern.
         * An external counter is updated once a second and then this
         * RAM array is filled with the new counter patterns. */
        16,     /* Play with sixteen LEDs */
        6,      /* 48 mS */
        /* buffer 1 */
//        32, 32, 32, 32,  32, 32, 32, 32,  32, 32, 32, 32,   32, 32, 32, 32,
//        /* buffer 2 */
//        32, 32, 32, 32,  32, 32, 32, 32,  32, 32, 32, 32,   32, 32, 32, 32
    };

const uint8_t Clock[] = {
        /* This is another example of a dynamically updated LED pattern.
         * An external clock is updated once a second and then this
         * RAM array is filled with the new clock patterns. */
        20,     /* Play with twenty LEDs */
        125,    /* 1000 mS */
        /* buffer 1 */
//        32, 32, 32, 32,  32, 32, 32,    /* seconds units & tens BCD digits */
//        32, 32, 32, 32,  32, 32, 32,    /* minutes units & tens BCD digits */
//        32, 32, 32, 32,  32, 32,         /* hours units & tens BCD digits */
//        /* buffer 2 */
//        32, 32, 32, 32,  32, 32, 32,    /* seconds units & tens BCD digits */
//        32, 32, 32, 32,  32, 32, 32,    /* minutes units & tens BCD digits */
//        32, 32, 32, 32,  32, 32         /* hours units & tens BCD digits */
    };

const uint8_t binaryDigitMap[] = {
        32, 32, 32, 32, 
         0, 32, 32, 32,
        32,  1, 32, 32, 
         0,  1, 32, 32,
        32, 32,  2, 32,
         0, 32,  2, 32,
        32,  1,  2, 32,
         0,  1,  2, 32, 
        32, 32, 32,  3,
         0, 32, 32,  3,
        32,  1, 32,  3,
         0,  1, 32,  3,
        32, 32,  2,  3,
         0, 32,  2,  3,
        32,  1,  2,  3,
         0,  1,  2,  3,
    };

const uint8_t * Sequence_Sets[] = {
    &Runway[0], &Scan[0], &Random[0], &Broadway[0], &DoubleScan[0], &Snow[0],
    &ScanTarget[0], &Clock[0], &ScanOut[0], &Sparks[0], &QuadScan[0], &Counter[0],
    &Target[0], &Blank[0], &Check[0], &Version[0]
};

const uint16_t Sequence_Size[] = {
    sizeof(Runway), sizeof(Scan), sizeof(Random), sizeof(Broadway), sizeof(DoubleScan),
    sizeof(Snow), sizeof(ScanTarget), 42 /* Clock */, sizeof(ScanOut), sizeof(Sparks),
    sizeof(QuadScan), 34 /* Counter */, sizeof(Target), sizeof(Blank), 66 /* Check) */,
    sizeof(Version)
};

static uint16_t pause = 24;         // 24 mS default pause
static uint16_t size = 0;
static uint8_t prev = 32;           // Force an initial sequence choice
static uint8_t* active = 0;         // LED array to be scanned
static uint16_t counter = 15000;
static uint16_t powerup = 0;        // Power up scan LEDs lit
static uint8_t seconds = 0x30;      // Time variables
static uint8_t minutes = 0x55;
static uint8_t hours   = 0x20;

static uint8_t scanLED1 = 0;        // active scan LED for scanBuffer1
static uint8_t scanMAX1 = 0;        // maximum LED to scan for scanBuffer1
static uint8_t scanLED2 = 0;        // active scan LED for scanBuffer2
static uint8_t scanMAX2 = 0;        // maximum LED to scan for scanBuffer2
static uint16_t scanTimer = 0;      // LED animation timer
static uint8_t* scanBuffer1 = 0;    // Double-buffered scanning for LEDs
static uint8_t* scanBuffer2 = 0;
static uint8_t scanActiveBuffer = 0;// Active scanning buffer
static uint16_t scanIndex = 0;      // current LED start position in active[]

void Sequences_SetActive (uint8_t choice) {
    uint8_t i;

    if (choice != prev && choice < sizeof(Sequence_Sets)) {
        active = (uint8_t *)Sequence_Sets[choice];
        size = Sequence_Size[choice];

        /* dynamic animations use the global buffer */
        if (active == Clock || active == Counter || active == Check) {
            // copy over the number of LEDs used and animation delay
            DisplayBuffer[0] = active[0];
            DisplayBuffer[1] = active[1];

            // clear the animation buffers
            for (i=2; i<size; i++) DisplayBuffer[i] = 32;

            // use the global animation buffer
            active = DisplayBuffer;
        }

        prev = choice;
        scanIndex = size;
        scanTimer = 0;   /* force a buffer refresh */
    }
}

void Sequences_SetPause (uint16_t milliSeconds) {
    pause = milliSeconds;       // 1 millisecond per bit
}

static void SetDigit (uint8_t digit, uint8_t led, uint8_t value, uint8_t numBits) {
    uint8_t bits, i;
    uint8_t num;
    uint16_t index;

    i=0;
    for (bits=0; bits<numBits; bits++) {
        index = ((uint16_t)value<<2)+i;
        num = binaryDigitMap[index];
        if (num != 32) num += led;
        DisplayBuffer[digit] = num;
        digit++; i++;
    }
}

static uint8_t BCD_Increment (uint8_t* bcd, uint8_t max) {
    uint8_t digit = *bcd;

    /* Add one to the bcd number */
    if (digit == max) {
        *bcd = 0;
        return 1;  // carry to next digits
    } else {
        if ((digit & 0xF) == 9) {
            *bcd = (digit & 0xF0) + 0x10;
        } else {
            *bcd = digit+1;
        }
    }
    return 0;   // no carry
}

static void UpdateDigits (uint16_t scan) {
    // Special case where a counter was selected
    uint16_t i;
    uint8_t *display;

    if (active != DisplayBuffer) return;
    display = (uint8_t *)Sequence_Sets[prev];

    /* programmatic update of the display buffers */
    if (display == Counter) {
        // Update the counter
        counter++;

        // Update the counter digits
        SetDigit(scan, 2, counter & 0xF, 4);
        SetDigit(scan+4, 10, (counter >> 4) & 0xF, 4);
        SetDigit(scan+8, 18, (counter >> 8) & 0xF, 4);
        SetDigit(scan+12, 24, (counter >> 12) & 0xF, 4);
    } else if (display == Clock) {
        // Update the clock
        if (BCD_Increment(&seconds, 0x59)) {
            if (BCD_Increment(&minutes, 0x59)) {
                BCD_Increment(&hours, 0x23);
            }
        }

        // Update the clock digits
        SetDigit(scan,  2, seconds & 0xF, 4);
        SetDigit(scan+4,  7, seconds >> 4, 3);
        SetDigit(scan+7, 12, minutes & 0xF, 4);
        SetDigit(scan+11, 17, minutes >> 4, 3);
        SetDigit(scan+14, 22, hours & 0xF, 4);
        SetDigit(scan+18, 27, hours >> 4, 2);
    } else if (display == Check) {
        for (i=scan; i<=scan+powerup; i++) DisplayBuffer[i] = i-scan;

        // Cause LEDs to sequence on from lowest to highest
        if (powerup < 31) powerup++;
    }
}

void Sequences_Play (uint16_t time) {
    uint16_t delay = active[1];
    uint16_t fsize = active[0];
    uint16_t duration = (delay != 0) ? (delay << 3) : pause;
    uint16_t loops = (time * 1000) / ((size / fsize) * duration);
    if (loops == 0) loops = 2; else loops++;
    while (loops > 0) {
        /* Handle sequence counter updates at the right time */
        if (scanTimer == 0) {
            /* set up next timer interval */
            if (active[1] != 0) {
                scanTimer = ((uint16_t)active[1]) << 3;
            } else {
                scanTimer = pause;
            }

            /* set up the next LED sequence to display */
            if (scanIndex < size-active[0])
                scanIndex += active[0];
            else {
                scanIndex = 2; loops--;
            }
            UpdateDigits(scanIndex);
            if (scanActiveBuffer == 0) {
                /* using scanBuffer1 so set up scanBuffer2 */
                scanBuffer2 = &active[scanIndex];
                scanMAX2 = active[0];
                scanLED2 = 0;
                while (scanLED1 != 0);      // wait for current cycle to complete
                scanActiveBuffer = 1;       // switch over to this buffer
            } else {
                /* using scanBuffer2 so set up scanBuffer1 */
                scanBuffer1 = &active[scanIndex];
                scanMAX1 = active[0];
                scanLED1 = 0;
                while (scanLED2 != 0);      // wait for current cycle to complete
                scanActiveBuffer = 0;       // switch over to this buffer
            }
        }
    }
}

void Sequences_Update (void) {
    /* Interrupt sequence handler -- invoked every millisecond */
    if (scanActiveBuffer == 0) {
        if (scanMAX1 != 0) {
            LEDs_TurnOn(scanBuffer1[scanLED1++]);
            if (scanLED1 == scanMAX1) scanLED1 = 0;
        }
    } else {
        if (scanMAX2 != 0) {
            LEDs_TurnOn(scanBuffer2[scanLED2++]);
            if (scanLED2 == scanMAX2) scanLED2 = 0;
        }
    }
    if (scanTimer) scanTimer--;
}

void Sequences_Init (void) {
    // Set up Timer 2 registers for 1 mS interrupts
    T2CONbits.TMR2ON = 0;	// Stop Timer2
    PR2 = FCY >> 2;             // Timer period value
    PIR1bits.TMR2IF = 0;	// Clear Timer2 interrupt flag bit
    T2CONbits.T2CKPS = 0b01;	// Set up Timer2 prescale to /4
    T2CONbits.TMR2ON = 1;	// Enable Timer2
    PIE1bits.TMR2IE = 1;        // Enable timer interrupts
}
