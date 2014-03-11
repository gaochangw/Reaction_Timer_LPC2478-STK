/***********************************************************************
 * File:     reaction_timer.c
 * Project:  Reaction Timer Using ARM7 Microprocessor
 * Rev:      1.0
 * Author:   Chang Gao
 * Date:     06 Feb 2014
 *
 * Description:
 *     This is a project for year 2 student in University of Liverpool.
 *     The programme is an example of reaction timer based on the 
 *     OLIMEX LPC2478-STK Board.
 *
 * Revision History:
 * Rev 1.0 06 Feb 2014
 *
 * Many thanks to Chun Sing Chu's and Ivan Vasilev's work!
 **********************************************************************/
#include "LPC24xx.H"
#include "type.h"
#include "clcdc.h"
#include "lcd_params.h"
#include "lcd_driver.h"
#include "low_level_init.h"
#include "lcd_params.h"
#include "lcd_draw.h"
#include "lcd_text.h"
#include "irq.h"
#include "fio.h"
#include "adc.h"
#include "bitmap.h"
#include "target.h"
#include "uart.h"
#include "clock.h"
#include "menu.h"
#include "touch.h"
#include "clock/rtc.h"
#include <stdio.h>                    /* standard I/O .h-file                */
#include <ctype.h>                    /* character functions                 */
#include <string.h>                   /* string and memory functions         */
#include <stdlib.h>

extern __pinsel0_bits *PINSEL0_bit;
extern __pinsel1_bits *PINSEL1_bit;
extern __pinsel3_bits *PINSEL3_bit;
extern __adcr_bits    *AD0CR_bit; 
extern __adgdr_bits   *AD0GDR_bit;
extern __pconp_bits   *PCONP_bit;
extern __pinsel1_bits *PINMODE1_bit;
extern __gpio0_bits   *FIO0DIR_bit;

#define SW_JP14800      0x00000002 /* P2.1 */
#define LCD_DISPLAY AT070TN83
#define X_MIN 136
#define X_MAX 896
#define Y_MIN 152
#define Y_MAX 864

static INT32S dev_lcd;

volatile DWORD UART0Status;


INT32U num_frms;
BOOL first_frm;

INT32U dmatccount0, dmatccount1;
INT32U dmaerrcount0, dmaerrcount1;
BOOL dma_end_flag;


static INT32U x_pos, y_pos;
volatile DWORD eint0_counter;

/* Declarations */
void gpio0_handler(void);
void clcdc_handler(void);
void dma_handler(void);
INT32U invo(INT32U a,INT32U cnt);



/***********************************************************************
 *
 * Function: main
 *
 * Purpose: Function entry point from the startup code.
 *
 **********************************************************************/

INT32S main(void)
{
	
	/* Initialize low level of the Board */
	low_level_init();	// Initialize PLL,RAM,GPIO..
	UARTInit(115200);
	FIO3DIR=0x00FF0000;
  FIO3CLR=0x00FF0000;
	PINSEL0_bit  = (__pinsel0_bits *) &PINSEL0;
	PINSEL1_bit  = (__pinsel1_bits *) &PINSEL1;
	PINSEL3_bit  = (__pinsel3_bits *) &PINSEL3;
	AD0CR_bit    = (__adcr_bits *)    &AD0CR;
	AD0GDR_bit   = (__adgdr_bits *)   &AD0GDR;
  PCONP_bit    = (__pconp_bits *)   &PCONP;
	PINMODE1_bit = (__pinsel1_bits *) &PINMODE1;
	FIO0DIR_bit  = (__gpio0_bits *)   &FIO0DIR;
  
	/* Open LCD */
  if ((dev_lcd = lcd_open(CLCDC, (INT32S)&LCD_DISPLAY)) == 0x0)
	{
		return 0;	// Error opening the device
	}
    
  /* Set LCD display pointer */
  lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SDRAM_BASE);

  /* Turn on LCD */
  lcd_ioctl(dev_lcd, LCD_PWR_ON, 1);

  /* Enable LCD */
  lcd_ioctl(dev_lcd, LCD_ENABLE, 1);
	
  RTCInit();
	RTCStart();
	
	Menu_Main();
	return 0;
}

/***********************************************************************
 *
 * Function: gpio0_handler
 *
 * Purpose: gpio0_handler.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void gpio0_handler(void)
{
    if (IO_INT_STAT & 0x4)
    {
        /* Turn off LCD */
        lcd_ioctl(dev_lcd, LCD_PWR_ON, 0);

        /* Disable LCD */
        lcd_ioctl(dev_lcd, LCD_ENABLE, 0);

        /* Close LCD */
        lcd_close(dev_lcd);

        IO2_INT_CLR = SW_JP14800;       /* clear SW_JP14 interrupt */
        VICAddress = 0;               /* Acknowledge Interrupt */
    }
}
/***********************************************************************
 *
 * Function: clcdc_handler
 *
 * Purpose: CLCDC interrupt handler.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void clcdc_handler(void)
{		
    INT32S status;

    /* Get masked interrupt statu */
    status = lcd_ioctl(dev_lcd, LCD_GET_STATUS, LCD_GET_INTERRUPT);

    if (status & CLCDC_LCD_INTERRUPT_FUF)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_FUF);
    }
    if (status & CLCDC_LCD_INTERRUPT_LNBU)
    {
        num_frms++;

        if ((num_frms & 0x7F) == 0x0)
        {
           if (first_frm)
           {
              first_frm = FALSE;

              /* Set LCD display pointer */
              lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SRAM_BASE);
              x_pos += 32;
              if (x_pos > 800)
              {  
                 x_pos = 0;
                 y_pos += 32;
                 if (y_pos > 480)
                 {
                    y_pos = 0;
                 }  
              }   
              lcd_ioctl(dev_lcd, LCD_CRSR_XY, (INT32S)(((y_pos & 0x3FF) << 16) + (x_pos & 0x3FF)));
           }
           else
           {
              first_frm = TRUE;

              /* Set LCD display pointer */
              lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SDRAM_BASE);
              x_pos += 32;
              if (x_pos > 800)
              {  
                 x_pos = 0;
                 y_pos += 32;
                 if (y_pos > 480)
                 {
                    y_pos = 0;
                 }  
              }   
              lcd_ioctl(dev_lcd, LCD_CRSR_XY, (INT32S)(((y_pos & 0x3FF) << 16) + (x_pos & 0x3FF)));
           }
        }        

        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_LNBU);
    }
    if (status & CLCDC_LCD_INTERRUPT_VCOMP)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_VCOMP);
    }
    if (status & CLCDC_LCD_INTERRUPT_MBERROR)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_MBERROR);
    }

    VICAddress = 0; /* Acknowledge Interrupt */
}



/***********************************************************************
 *
 * Function: dma_handler
 *
 * Purpose: dma_handler.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void dma_handler(void)
{
    INT32U regval;

    regval = GPDMA_INT_TCSTAT;
    if (regval)
    {
        if (regval & 0x1)
        {
            dmatccount0++;
        }
        if (regval & 0x2)
        {
            dmatccount1++;
        }
        dma_end_flag = FALSE;
        GPDMA_INT_TCCLR |= regval;
    } 

    regval = GPDMA_INT_ERR_STAT;
    if (regval)
    {
        if (regval & 0x1)
        {
            dmaerrcount0++;
        }
        if (regval & 0x2)
        {
            dmaerrcount1++;
        }
        GPDMA_INT_ERR_CLR |= regval;
    } 
    VICAddress = 0;               /* Acknowledge Interrupt */
}

INT32U invo(INT32U a,INT32U cnt)
{
    INT32U b=0;
    INT32U i;
    for(i=0;i<cnt;i++)
    {
        if(a&(1<<(cnt-i-1)))
			(b |= 1<<i);
    }

    return b;
}


