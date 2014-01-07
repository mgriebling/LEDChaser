/* 
 * File:   LEDs.h
 * Author: Administrator
 *
 * Created on August 30, 2012, 7:24 AM
 */

#ifndef LEDS_H
#define	LEDS_H

#include <stdint.h>        /* For uint8_t definition */

#ifdef	__cplusplus
extern "C" {
#endif

extern void LEDs_TurnOn (uint8_t led);
extern void LEDs_AllOff (void);
extern void LEDs_Init (void);

#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

