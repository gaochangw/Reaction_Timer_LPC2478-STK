/***********************************************************************
 * File:   data_types.h
 * Rev:    1.0
 * Author: Chun Sing Chu
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains the typedefs for C standard types.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#ifndef __DATA_TYPES_H
#define __DATA_TYPES_H
#include "io_macros.h"

/***********************************************************************
 * Data  types definition                                  
 **********************************************************************/
typedef unsigned char   BOOL;
typedef unsigned char   BOOL1;
typedef unsigned char * pBOOL;
typedef unsigned char   INT8U;
typedef unsigned char * pINT8U;
typedef signed   char   INT8S;
typedef signed   char * pINT8S;
typedef unsigned short  INT16U;
typedef unsigned short* pINT16U;
typedef signed   short  INT16S;
typedef signed   short* pINT16S;
typedef unsigned int    INT32U;
typedef unsigned int  * pINT32U;
typedef signed   int    INT32S;
typedef signed   int  * pINT32S;

#ifndef TRUE
#define TRUE               1
#endif

#ifndef FALSE
#define FALSE              0
#endif

#ifndef NULL
#define NULL               ((void*)0)
#endif 

#define _NO_ERROR          (INT32S)(0)
#define _ERROR             (INT32S)(-1)

#define LongToBin(n) (((n >> 21) & 0x80) | \
                      ((n >> 18) & 0x40) | \
                      ((n >> 15) & 0x20) | \
                      ((n >> 12) & 0x10) | \
                      ((n >>  9) & 0x08) | \
                      ((n >>  6) & 0x04) | \
                      ((n >>  3) & 0x02) | \
                      ((n      ) & 0x01))

#define __BIN(n) LongToBin(0x##n##l)

#define BIN8(n)                       __BIN(n)
#define BIN(n)                        __BIN(n)
#define BIN16(b1,b2)        ((        __BIN(b1)  <<  8UL) + \
                                      __BIN(b2))
#define BIN32(b1,b2,b3,b4) ((((Int32U)__BIN(b1)) << 24UL) + \
                            (((Int32U)__BIN(b2)) << 16UL) + \
                            (((Int32U)__BIN(b3)) <<  8UL) + \
                              (Int32U)__BIN(b4))



#endif /* __DATA_TYPES_H */
