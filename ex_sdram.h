/*****************************************************************************
 *   ex_sdram.h:  Header file for NXP LPC24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2007.01.10  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __EX_SDRAM_H 
#define __EX_SDRAM_H

/*****************************************************************************
 * Defines and typedefs
 ****************************************************************************/

/* External Memory Controller (EMC) */
#define EMC_BASE_ADDR		0xFFE08000
#define EMC_CTRL       (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x000))
#define EMC_STAT       (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x004))
#define EMC_CONFIG     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x008))



/* Dynamic RAM access registers */
#define EMC_DYN_CTRL     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x020))
#define EMC_DYN_RFSH     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x024))
#define EMC_DYN_RD_CFG   (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x028))
#define EMC_DYN_RP       (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x030))
#define EMC_DYN_RAS      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x034))
#define EMC_DYN_SREX     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x038))
#define EMC_DYN_APR      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x03C))
#define EMC_DYN_DAL      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x040))
#define EMC_DYN_WR       (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x044))
#define EMC_DYN_RC       (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x048))
#define EMC_DYN_RFC      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x04C))
#define EMC_DYN_XSR      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x050))
#define EMC_DYN_RRD      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x054))
#define EMC_DYN_MRD      (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x058))

#define EMC_DYN_CFG0     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x100))
#define EMC_DYN_RASCAS0  (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x104))
#define EMC_DYN_CFG1     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x140))
#define EMC_DYN_RASCAS1  (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x144))
#define EMC_DYN_CFG2     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x160))
#define EMC_DYN_RASCAS2  (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x164))
#define EMC_DYN_CFG3     (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x180))
#define EMC_DYN_RASCAS3  (*(volatile unsigned long *)(EMC_BASE_ADDR + 0x184))

#define SDRAM_BASE_ADDR		0xA0000000
#define SDRAM_SIZE		0x02000000

void SDRAMInit(void);
void delayMs(INT32U delayInMs);
void ClearMemory(void);
int SDRAM_Test (void);

#endif /* end __EX_SDRAM_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
