/*****************************************************************************
 *   uart.c:  UART API file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.12  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC24xx.H"  /* LPC23xx/24xx definitions */
#include "type.h"
#include "target.h"
#include "uart.h"

volatile BYTE UART1TxEmpty = 1;

/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART1 port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			UART baudrate
** Returned value:		true or false, return false only if the 
**						interrupt handler can't be installed to the 
**						VIC table
** 
*****************************************************************************/
DWORD UARTInit( DWORD baudrate )
{
    DWORD Fdiv;
   /* Configure UART1 for 115200 baud. */
   PINSEL0 |=  0x40000000;                   /* Enable UART1 pins            */
   PINSEL1 |=  0x00000001;                   /* Enable UART1 pins            */

    U1LCR = 0x83;                             /* 8 bits, no Parity, 1 Stop bit*/
    Fdiv = ( Fpclk / 16 ) / baudrate ;	/*baud rate */
    U1DLM = Fdiv / 256;							
    U1DLL = Fdiv % 256;
    U1LCR = 0x03;		/* DLAB = 0 */
    U1FCR = 0x07;		/* Enable and reset TX and RX FIFO. */   
//    U1IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
    return (TRUE);
}


/*----------------------------------------------------------------------------
 *       sendchar:  Write a character to Serial Port
 *---------------------------------------------------------------------------*/
int sendchar (int ch) {
   if (ch == '\n') {
      while (!(U1LSR & 0x20));
      U1THR = '\r';
   }
   while (!(U1LSR & 0x20));
   return (U1THR = ch);
}

/*----------------------------------------------------------------------------
 *       getkey:  Read a character from Serial Port
 *---------------------------------------------------------------------------*/
int getkey (void) {
   while (!(U1LSR & 0x01));
   return (U1RBR);
}
/******************************************************************************
**                            End Of File
******************************************************************************/
