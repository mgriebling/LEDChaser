/******************************************************************************/
/* Main Files to Include                                                      */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <xc.h>

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* Refer to your Hi-Tech User Manual in the PICC installation directory       */
/* /doc folder for more information on filling in configuration bits.         */
/* In addition, configuration bit mnemonics can be found in your              */
/* PICC\version\include\<processor name>.h file for your device.  For         */
/* additional information about what the hardware configurations mean in      */
/* terms of device operation, refer to the device datasheet.                  */
/*                                                                            */
/******************************************************************************/

#ifdef _PIC16F690_H_
__CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_ON & FCMEN_ON);
#else
/* General syntax for configuration word 1 - Check your device .h file
for an up to date listing of available macros.*/
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_ON & BOREN_OFF);

/* If the device has multiple configuration words, the second macro defines
the second configuration word.  Again check your device .h file
for an up to date listing of available macros. */
__CONFIG(WRT_OFF & PLLEN_OFF & STVREN_OFF & BORV_HI & LVP_OFF);
#endif
