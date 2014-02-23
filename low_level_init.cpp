/***********************************************************************
 * File:   low_level_init.c
 * Rev:    1.0
 * Author: Chun Sing Chu
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains low level initialization of the LPC2478.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/
#include "LPC24xx.H"
#include "irq.h"
#include "low_level_init.h"
#include "ex_sdram.h"


/***********************************************************************
 *
 * Function: delayMs
 *
 * Purpose: Start the timer delay in micro seconds until elapsed.
 *
 * Processing:
 *
 * Parameters: 	Delay value in micro second
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void delayMs(INT32U delayInMs)
{
    T1TCR = 0x02; /* reset timer */
    T1PR  = 0x00; /* set prescaler to zero */
    T1MR0 = delayInMs * (18000000 / 1000); /* PCLK is 1/4 CCLK */ 

    T1IR  = 0xFF; /* reset all interrrupts */
    T1MCR = 0x04; /* stop timer on match */
    T1TCR = 0x01; /* start timer */
  
    /* wait until delay time has elapsed */
    while (T1TCR & 0x01);
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit( void )
{
	/* Reset all GPIO pins to default: primary function */
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
    PINSEL3 = 0x00000000;
    PINSEL4 = 0x00000000;
    PINSEL5 = 0x00000000;
    PINSEL6 = 0x00000000;
    PINSEL7 = 0x00000000;
    PINSEL8 = 0x00000000;
    PINSEL9 = 0x00000000;
    PINSEL10 = 0x00000000;
    
    IODIR0 = 0x00000000;
    IODIR1 = 0x00000000;
	IOSET0 = 0x00000000;
    IOSET1 = 0x00000000;
    
    FIO0DIR = 0x00000000;
    FIO1DIR = 0x00000000;
    FIO2DIR = 0x00000000;
    FIO3DIR = 0x00000000;
    FIO4DIR = 0x00000000;
    
    FIO0SET = 0x00000000;
    FIO1SET = 0x00000000;
    FIO2SET = 0x00000000;
    FIO3SET = 0x00000000;
    FIO4SET = 0x00000000;
    return;        
}

/***********************************************************************
 *
 * Function: configure_pll
 *
 * Purpose: switching to main OSC from IRC.
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
void configure_pll(void)
{
    INT16U MValue, NValue;

    if ((PLLSTAT&(0x04000000)))
	//if ( PLLSTAT & (1 << 25) )
    {
		//PLLCON &= ~(1<<1);	   /* PLL disconnected */
        PLLCON = 1;
		PLLFEED = 0xaa;
        PLLFEED = 0x55;
    }

     
    PLLCON = 0;		/* PLL disabled */
	PLLFEED = 0xaa;
    PLLFEED = 0x55;
    
	SCS|=(1<<5);  /* Enable main OSC */
    while(!(SCS&0x40)); /* Wait until main OSC is usable */
	// while( !(SCS & 0x40) );
	//CLKSRCSEL &=0x0;
	//CLKSRCSEL |=0x1;					/* select main OSC, 12MHz, as the PLL clock source */
	CLKSRCSEL = 0x1;

	PLLCFG = PLL_MValue | (PLL_NValue << 16);
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
      
	//PLLCON |=0x1;			/* PLL enabled */
    PLLCON = 1;
	PLLFEED = 0xaa;
    PLLFEED = 0x55;

	CCLKCFG = CCLKDivValue;	/* Set clock divider */

   while ( ((PLLSTAT & (1 << 26)) == 0) );	/* Check lock bit status */
	  MValue = (PLLSTAT&0x00007fff);
	  NValue = ((PLLSTAT&0x00ff0000)>>16);
    while ((MValue != PLL_MValue) && (NValue != PLL_NValue));

    //PLLCON |= (1<<1); /* PLL connected */
    PLLCON = 3;	
	PLLFEED = 0xaa;
    PLLFEED = 0x55;
	while ( ((PLLSTAT & (1 << 25)) == 0) );
	return;
}

/***********************************************************************
 *
 * Function: low_level_init
 *
 * Purpose: initialize the chip.
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
void low_level_init(void)
{
    /* Configure PLL, switch from IRC to Main OSC */
    configure_pll();
	GPIOResetInit();

   // PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
   // PCLKSEL1 = 0x00000000;

	PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
    PCLKSEL1 = 0xAAAAAAAA;


    SDRAMInit();
    ClearMemory();
//	if(!SDRAM_Test ())
		//sendchar('o');                        /* ³ö´í´¦Àí */ 

    PCONP |= 0x00100000;        /* Power Control for CLCDC */ 

    /* Set memory accelerater module*/
    MAMCR = 0;
    MAMTIM = 3; /* Fcclk > 40MHz */
//    MAMTIM = 2; /* Fcclk >= 20MHz */
//    MAMTIM = 1; /* Fcclk < 20MHz */
    MAMCR = 2;
 
#ifdef __DEBUG_RAM    
    MEMMAP = 0x2;			/* remap to internal RAM */
#endif

#ifdef __DEBUG_FLASH    
    MEMMAP = 0x1;			/* remap to internal flash */
#endif 
   
}
