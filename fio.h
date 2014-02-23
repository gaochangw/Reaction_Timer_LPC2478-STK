/*****************************************************************************
 *   fio.h:  Header file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __FIO_H 
#define __FIO_H

/* bit 0 in SCS register, port 0/1 are regular ports when bit 0 
is 0,  fast ports when bit 0 is 1. */
#define GPIOM			0x00000001

/* see master definition file lpc230x.h for more details */
#define REGULAR_PORT_DIR_BASE		GPIO_BASE_ADDR + 0x08
#define REGULAR_PORT_DIR_INDEX		0x10	

#define HS_PORT_DIR_BASE			FIO_BASE_ADDR + 0x00
#define HS_PORT_DIR_INDEX			0x20

#define FAST_PORT		0x01
#define REGULAR_PORT	0x02

#define DIR_OUT			0x01
#define DIR_IN			0x02


#define D6_ON()  (FIO3SET = (1 << 20))
#define D5_ON()  (FIO3SET = (1 << 19))
#define D4_ON()  (FIO3SET = (1 << 18))
#define D7_ON()  (FIO3SET = (1 << 21))
#define D8_ON()  (FIO3SET = (1 << 22))
#define D3_ON()  (FIO3SET = (1 << 17))
#define D2_ON()  (FIO3SET = (1 << 16))
#define D9_ON()  (FIO3SET = (1 << 23))

#define D6_OFF()  (FIO3CLR = (1 << 20))
#define D5_OFF()  (FIO3CLR = (1 << 19))
#define D4_OFF()  (FIO3CLR = (1 << 18))
#define D7_OFF()  (FIO3CLR = (1 << 21))
#define D8_OFF()  (FIO3CLR = (1 << 22))
#define D3_OFF()  (FIO3CLR = (1 << 17))
#define D2_OFF()  (FIO3CLR = (1 << 16))
#define D9_OFF()  (FIO3CLR = (1 << 23))

extern void GPIOInit( DWORD PortNum, DWORD PortType, DWORD PortDir );

#endif /* end __FIO_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
