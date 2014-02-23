/****************************************************************************
 *
 * Project: LPC-2478-STK
 *
 * Copyright: Ivan Vasilev, Olimex Ltd. All rights reserved.
 *
 * File: adc.h
 * Description: ADC functionality
 * Developer: Ivan Vasilev, <ivan at l123.org>
 *
 * Last change: $Date: 2008-07-01 14:12:20 +0300 (???????, 01 ??? 2008) $
 * Revision: $Revision: 58 $
 * Id: $Id: iBMapp.c 58 2008-07-01 11:12:20Z Ivan $
 * Author: $Author: Ivan $
 *
 ****************************************************************************/
#include "LPC24xx.h"
#include "data_types.h"

#include "adc.h"
#include "target.h"
#include "bitmap.h"


	__pinsel0_bits *PINSEL0_bit;
	__pinsel1_bits *PINSEL1_bit;
	__pinsel3_bits *PINSEL3_bit;
    __adcr_bits * AD0CR_bit;
	__adgdr_bits * AD0GDR_bit;
    __pconp_bits * PCONP_bit;
	__pinsel1_bits *PINMODE1_bit;
	__gpio0_bits *FIO0DIR_bit;


void 	InitADC(INT8U channel)
{
	
	INT8U div;
	

	
	if (channel > 7) channel = 0;
	
	  PCONP_bit->PCAD = 1;
    //PCONP |= (1 << 12);           /* Enable power to AD block */
	  SCS = SCS|1;
	
	
	switch (channel)
	{
		case 0:
			PINSEL1_bit->P0_23 = 0x01;
			break;
		
		case 1:
			PINSEL1_bit->P0_24 = 0x01;
			break;
			
		case 2:
			PINSEL1_bit->P0_25 = 0x01;
			break;
			
		case 3:
			PINSEL1_bit->P0_26 = 0x01;
			break;
			
		case 4:
			PINSEL3_bit->P1_30 = 0x03;
			break;
			
		case 5:
			PINSEL3_bit->P1_31 = 0x03;
			break;
			
		case 6:
			PINSEL0_bit->P0_12 = 0x03;
			break;
			
		case 7:
			PINSEL0_bit->P0_13 = 0x03;
			break;
	}
	
	
//	div = (SYS_GetFpclk(ADC_PCLK_OFFSET) / ADC_CLOCK_RATE) + 1;
	
	div=Fpclk/2/ADC_CLOCK_RATE+1;

	AD0CR_bit->CLKDIV = div;
	AD0CR_bit->BURST = 0;
	AD0CR_bit->START = 0;
	AD0CR_bit->PDN = 1;
	
}

INT32U GetADC(INT8U channel)
{
	INT32U result;
	
	if (channel > 7) channel = 0;
	AD0CR_bit->SEL = 1<<channel; /* select the channel */
	AD0CR_bit->START  = 0x01;
	
	while (!AD0GDR_bit->DONE);	/* wait for completion */
	
	AD0CR_bit->START = 0x0;
	
	if (AD0GDR_bit->OVERUN == 1) return 0;
	
	result = AD0GDR_bit->RESULT;
	
	return result;	
}
