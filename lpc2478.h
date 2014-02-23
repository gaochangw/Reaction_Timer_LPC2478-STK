/***********************************************************************
 * File:   lpc2478.h
 * Rev:    1.0
 * Author: Chun Sing Chu
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains definitions specific to LPC2478.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#ifndef LPC2478_H
#define LPC2478_H

#include "data_types.h"

/* LCD controller base address */
#define LCD_BASE (0xFFE10000)

/* LCD controller clock CFG register */
#define CLCDCLKCFG *(volatile INT32U *)(0xE01FC1B8)

/* LCD controller pin select register */
#define CLCDPINSEL *(volatile INT32U *)(0xE002C02C)

/* SRAM base address */
#define SRAM_BASE (0x80000000)

/* SDRAM base address */
#define SDRAM_BASE (0xA0000000)

/* SDRAM end address */
#define SDRAM_END  (0xA2000000)

#endif /* LPC2478_H */ 
