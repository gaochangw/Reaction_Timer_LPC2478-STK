/***********************************************************************
 * File:   lcd_params.c
 * Rev:    1.0
 * Author: Chun Sing Chu
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains parameters for LCD panel used on FCC1 board.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 *
 **********************************************************************/

#include "lcd_params.h"

/* Hantronix HDA700L landscape mode display */
const LCD_PARAM_T AT070TN83 =
{
    70,       /* Horizontal back porch */
    30,       /* Horizontal front porch */
    1,        /* HSYNC pulse width */
    800,      /* Pixels per line */
    13,       /* Vertical back porch */
    20,       /* Vertical front porch */
    1,        /* VSYNC pulse width */
    480,      /* Lines per panel */
    0,        /* Do not invert output enable */
    0,        /* Do not invert panel clock */
    0,        /* Invert HSYNC */
    0,        /* Invert VSYNC */
    1,        /* AC bias frequency (not used) */
    16,       /* Bits per pixel */
    27000000, /* Optimal clock rate (Hz) */
    TFT,      /* LCD panel type */
    0,        /* Single panel display */
};
