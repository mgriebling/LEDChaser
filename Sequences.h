/* 
 * File:   Sequences.h
 * Author: mikeg
 *
 * Created on August 31, 2012, 8:14 AM
 */

#ifndef SEQUENCES_H
#define	SEQUENCES_H

#include <stdint.h>        /* For uint8_t definition */

#ifdef	__cplusplus
extern "C" {
#endif

extern void Sequences_SetActive (uint8_t active);
extern void Sequences_SetPause (uint16_t milliSeconds);
extern void Sequences_Play (uint16_t count);
extern void Sequences_Update (void);
extern void Sequences_Init (void);

#ifdef	__cplusplus
}
#endif

#endif	/* SEQUENCES_H */

