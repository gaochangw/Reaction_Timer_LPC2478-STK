/****************************************************************************
 *
 * Project: LPC-2478-STK
 *
 * Copyright: Ivan Vasilev, Olimex Ltd. All rights reserved.
 *
 * File: touch.c
 * Description: touchscreen include file
 * Developer: Ivan Vasilev, <ivan at l123.org>
 *
 * Last change: $Date: 2008-07-01 14:12:20 +0300 (???????, 01 ??? 2008) $
 * Revision: $Revision: 58 $
 * Id: $Id: iBMapp.c 58 2008-07-01 11:12:20Z Ivan $
 * Author: $Author: Ivan $
 *
 ****************************************************************************/
#include "LPC24xx.h"
#include "touch.h"
#include "adc.h"
#include "bitmap.h"
#include "lcd_text.h"
#include "lcd_draw.h"

extern __pinsel0_bits *PINSEL0_bit;
extern __pinsel1_bits *PINSEL1_bit;
extern __pinsel3_bits *PINSEL3_bit;
extern __adcr_bits * AD0CR_bit; 
extern __adgdr_bits * AD0GDR_bit;
extern __pconp_bits * PCONP_bit;
extern __pinsel1_bits *PINMODE1_bit;
extern __gpio0_bits *FIO0DIR_bit;

touchscreen_data res_data;

void polarizeXx(void)
{
	PINSEL1_bit->P0_24 = 0x00;
	PINSEL1_bit->P0_22 = 0x00;
	FIO0DIR_bit->P0_24 = 0x01;
	FIO0DIR_bit->P0_22 = 0x01;
	
	FIO0SET = 1<<24;
	FIO0CLR = 1<<22;
}

void polarizexX(void)
{
	PINSEL1_bit->P0_24 = 0x00;
	PINSEL1_bit->P0_22 = 0x00;
	FIO0DIR_bit->P0_24 = 0x01;
	FIO0DIR_bit->P0_22 = 0x01;
	
	FIO0CLR = 1<<24;
	FIO0SET = 1<<22;
}

void polarizeYy(void)
{
	PINSEL1_bit->P0_23 = 0x00;
	PINSEL1_bit->P0_21 = 0x00;
	FIO0DIR_bit->P0_23 = 0x01;
	FIO0DIR_bit->P0_21 = 0x01;
	
	FIO0SET = 1<<23;
	FIO0CLR = 1<<21;
}

void polarizeyY(void)
{
	PINSEL1_bit->P0_23 = 0x00;
	PINSEL1_bit->P0_21 = 0x00;
	FIO0DIR_bit->P0_23 = 0x01;
	FIO0DIR_bit->P0_21 = 0x01;
	
	FIO0CLR = 1<<23;
	FIO0SET = 1<<21;
}

void	InitTS(touchscreen_data ts_resolution)
{
	if (ts_resolution.xvalue != 0)
	{
		res_data.xvalue = ts_resolution.xvalue;
	}
	else
	{
		res_data.xvalue = X_DEFAULT_RESOLUTION;
	}
	
	if (ts_resolution.yvalue != 0)
	{
		res_data.yvalue = ts_resolution.yvalue;
	}
	else
	{
		res_data.yvalue = Y_DEFAULT_RESOLUTION;
	}
	
	if (ts_resolution.pvalue != 0)
	{
		res_data.pvalue = ts_resolution.pvalue;
	}
	else
	{
		res_data.pvalue = P_DEFAULT_RESOLUTION;
	}
	
}

void ts_settling_delay(void)
{
	int i;
	for (i = TS_SETTLING_DELAY; i; i--);
}

touchscreen_data	GetTS(void)
{
	
#define XDELTA_MAX	100
#define	YDELTA_MAX	100
	touchscreen_data samples[TS_NUM_SAMPLES*2];
	/*static*/ /*touchscreen_data ts_result_p, ts_result_n, ts_result;*/
	touchscreen_data ts_result;
	int i;
	int yvalue_min = 1023;
	int yvalue_max = 0;
	int xvalue_min = 1023;
	int xvalue_max = 0;
	int xdelta, ydelta;
	int ts_max_value = 2<<(TS_RESOLUTION_BITS-1);
	
	float x_sample, y_sample;	// For coordinates approximation (Gao)
	
	ts_settling_delay();
	ts_settling_delay();
	ts_settling_delay();
	
	for ( i=0; i<TS_NUM_SAMPLES; i++)
	{
		FIO0DIR_bit->P0_21 = 0;
		PINMODE1_bit->P0_21 = 0x02;
		PINMODE1_bit->P0_23 = 0x02;
		polarizeXx();
		InitADC(TS_Y_CHANNEL);
		ts_settling_delay();
		samples[i*2].xvalue = GetADC(TS_Y_CHANNEL);
		
		FIO0DIR_bit->P0_22 = 0;
		PINMODE1_bit->P0_22 = 0x02;
		PINMODE1_bit->P0_24 = 0x02;
		polarizeYy();
		InitADC(TS_X_CHANNEL);
		ts_settling_delay();
		samples[i*2].yvalue = GetADC(TS_X_CHANNEL);
		
		samples[i*2].pvalue = 0;

		
		FIO0DIR_bit->P0_21 = 0;
		PINMODE1_bit->P0_21 = 0x02;
		PINMODE1_bit->P0_23 = 0x02;
		polarizexX();
		InitADC(TS_Y_CHANNEL);
		ts_settling_delay();
		samples[(i*2)+1].xvalue = GetADC(TS_Y_CHANNEL);
		
		FIO0DIR_bit->P0_22 = 0;
		PINMODE1_bit->P0_22 = 0x02;
		PINMODE1_bit->P0_24 = 0x02;
		polarizeyY();
		InitADC(TS_X_CHANNEL);
		ts_settling_delay();
		samples[(i*2)+1].yvalue = GetADC(TS_X_CHANNEL);
		
		samples[(i*2)+1].pvalue = 0;
		
	}
	
	ts_result.xvalue = 0;
	ts_result.yvalue = 0;
	ts_result.pvalue = 0;
		
	for (i = 0; i<(TS_NUM_SAMPLES	); i++)
	{
		int tempyval = ts_max_value - samples[i*2+1].yvalue;
		int tempxval = ts_max_value - samples[i*2+1].xvalue;
		
		ts_result.xvalue += samples[i*2].xvalue;
		ts_result.yvalue += samples[i*2].yvalue;
		
		ts_result.xvalue += ((ts_max_value)-samples[(i*2)+1].xvalue);
		ts_result.yvalue += ((ts_max_value)-samples[(i*2)+1].yvalue);
		
		
		if (yvalue_min > samples[i*2].yvalue) yvalue_min = samples[i*2].yvalue;
		if (yvalue_max < samples[i*2].yvalue) yvalue_max = samples[i*2].yvalue;
		
		if (yvalue_min > tempyval) yvalue_min = tempyval;
		if (yvalue_min < tempyval) yvalue_max = tempyval;
		
		if (xvalue_min > samples[i*2].xvalue) xvalue_min = samples[i*2].xvalue;
		if (xvalue_max < samples[i*2].xvalue) xvalue_max = samples[i*2].xvalue;
		
		if (xvalue_min > tempxval) xvalue_min = tempxval;
		if (xvalue_min < tempxval) xvalue_max = tempxval;
	}
	
	
	ts_result.xvalue = ts_result.xvalue / (TS_NUM_SAMPLES*2);
	ts_result.yvalue = ts_result.yvalue / (TS_NUM_SAMPLES*2);
	
	xdelta = xvalue_max - xvalue_min;
	ydelta = yvalue_max - yvalue_min;
	
	if (	(ts_result.xvalue < 910) && \
		(ts_result.yvalue < 910) && \
		(xdelta < XDELTA_MAX) && \
		(ydelta < YDELTA_MAX) )
	{
		ts_result.pvalue = 1024;
	}
	else
	{
		ts_result.pvalue = 0;
	}
	
	ts_result.yvalue = ts_max_value - ts_result.yvalue;
	
	/* Coordinate Approximation */
	x_sample = ts_result.xvalue;
	y_sample = ts_result.yvalue;
	if(ts_result.pvalue > 1000)
	{
		ts_result.xvalue = (INT16U)((x_sample - 100) * TS_X_RATIO);
		ts_result.yvalue = (INT16U)((y_sample - 165) * TS_Y_RATIO);
	}
	else
	{
		ts_result.xvalue = 0;
		ts_result.yvalue = 0;
	}
	
	return ts_result;
	
}
touchscreen_data	GetTS_Fast(void)
{
	
#define XDELTA_MAX	100
#define	YDELTA_MAX	100
	touchscreen_data samples[TS_NUM_SAMPLES*2];
	/*static*/ /*touchscreen_data ts_result_p, ts_result_n, ts_result;*/
	touchscreen_data ts_result;
	int i;
	int yvalue_min = 1023;
	int yvalue_max = 0;
	int xvalue_min = 1023;
	int xvalue_max = 0;
	int xdelta, ydelta;
	int ts_max_value = 2<<(TS_RESOLUTION_BITS-1);
	
	float x_sample, y_sample;	// For coordinates approximation (Gao)
	
	for ( i=0; i<TS_NUM_SAMPLES; i++)
	{
		FIO0DIR_bit->P0_21 = 0;
		PINMODE1_bit->P0_21 = 0x02;
		PINMODE1_bit->P0_23 = 0x02;
		polarizeXx();
		InitADC(TS_Y_CHANNEL);
		ts_settling_delay();
		samples[i*2].xvalue = GetADC(TS_Y_CHANNEL);
		
		FIO0DIR_bit->P0_22 = 0;
		PINMODE1_bit->P0_22 = 0x02;
		PINMODE1_bit->P0_24 = 0x02;
		polarizeYy();
		InitADC(TS_X_CHANNEL);
		ts_settling_delay();
		samples[i*2].yvalue = GetADC(TS_X_CHANNEL);
		
		samples[i*2].pvalue = 0;

		
		FIO0DIR_bit->P0_21 = 0;
		PINMODE1_bit->P0_21 = 0x02;
		PINMODE1_bit->P0_23 = 0x02;
		polarizexX();
		InitADC(TS_Y_CHANNEL);
		ts_settling_delay();
		samples[(i*2)+1].xvalue = GetADC(TS_Y_CHANNEL);
		
		FIO0DIR_bit->P0_22 = 0;
		PINMODE1_bit->P0_22 = 0x02;
		PINMODE1_bit->P0_24 = 0x02;
		polarizeyY();
		InitADC(TS_X_CHANNEL);
		ts_settling_delay();
		samples[(i*2)+1].yvalue = GetADC(TS_X_CHANNEL);
		
		samples[(i*2)+1].pvalue = 0;
		
	}
	
	ts_result.xvalue = 0;
	ts_result.yvalue = 0;
	ts_result.pvalue = 0;
		
	for (i = 0; i<(TS_NUM_SAMPLES	); i++)
	{
		int tempyval = ts_max_value - samples[i*2+1].yvalue;
		int tempxval = ts_max_value - samples[i*2+1].xvalue;
		
		ts_result.xvalue += samples[i*2].xvalue;
		ts_result.yvalue += samples[i*2].yvalue;
		
		ts_result.xvalue += ((ts_max_value)-samples[(i*2)+1].xvalue);
		ts_result.yvalue += ((ts_max_value)-samples[(i*2)+1].yvalue);
		
		
		if (yvalue_min > samples[i*2].yvalue) yvalue_min = samples[i*2].yvalue;
		if (yvalue_max < samples[i*2].yvalue) yvalue_max = samples[i*2].yvalue;
		
		if (yvalue_min > tempyval) yvalue_min = tempyval;
		if (yvalue_min < tempyval) yvalue_max = tempyval;
		
		if (xvalue_min > samples[i*2].xvalue) xvalue_min = samples[i*2].xvalue;
		if (xvalue_max < samples[i*2].xvalue) xvalue_max = samples[i*2].xvalue;
		
		if (xvalue_min > tempxval) xvalue_min = tempxval;
		if (xvalue_min < tempxval) xvalue_max = tempxval;
	}
	
	
	ts_result.xvalue = ts_result.xvalue / (TS_NUM_SAMPLES*2);
	ts_result.yvalue = ts_result.yvalue / (TS_NUM_SAMPLES*2);
	
	xdelta = xvalue_max - xvalue_min;
	ydelta = yvalue_max - yvalue_min;
	
	if (	(ts_result.xvalue < 910) && \
		(ts_result.yvalue < 910) && \
		(xdelta < XDELTA_MAX) && \
		(ydelta < YDELTA_MAX) )
	{
		ts_result.pvalue = 1024;
	}
	else
	{
		ts_result.pvalue = 0;
	}
	
	ts_result.yvalue = ts_max_value - ts_result.yvalue;
	
	/* Coordinate Approximation */
	x_sample = ts_result.xvalue;
	y_sample = ts_result.yvalue;
	if(ts_result.pvalue > 1000)
	{
		ts_result.xvalue = (INT16U)((x_sample - 100) * TS_X_RATIO);
		ts_result.yvalue = (INT16U)((y_sample - 165) * TS_Y_RATIO);
	}
	else
	{
		ts_result.xvalue = 0;
		ts_result.yvalue = 0;
	}
	
	return ts_result;
	
}

void Touch_Test(void)
{
	#define X_OFFSET 0
	#define Y_OFFSET 10
	float r = 4;	// Brush size
	char str[8];
	Cursor strCursor1, strCursor2, strCursor3,
	       strCursor4, strCursor5, strCursor6,
				 buttonCursor;// String cursor
	touchscreen_data ts_data;
	
	Lcd_ClearScr(320,240,0xFFFF);
	strCursor1 = Set_Cursor(16 + X_OFFSET,0 + Y_OFFSET);
	strCursor2 = Set_Cursor(16 + X_OFFSET,16 + Y_OFFSET);
	strCursor3 = Set_Cursor(16 + X_OFFSET,32 + Y_OFFSET);
	strCursor4 = Set_Cursor(0 + X_OFFSET,0 + Y_OFFSET);
	strCursor5 = Set_Cursor(0 + X_OFFSET,16 + Y_OFFSET);
	strCursor6 = Set_Cursor(0 + X_OFFSET,32 + Y_OFFSET);
	GLCD_printf("x:", 0x0000, 0xffff, strCursor4);
	GLCD_printf("y:", 0x0000, 0xffff, strCursor5);
	GLCD_printf("p:", 0x0000, 0xffff, strCursor6);
	
	GLCD_RoundRect(10,90,80,110,5,LIGHT_BLUE);
	GLCD_RoundRect(10,90,120,150,5,LIGHT_BLUE);
	GLCD_RoundRect(10,90,160,190,5,LIGHT_BLUE);
	GLCD_RoundRect(10,90,200,230,5,LIGHT_BLUE);
	buttonCursor = Set_Cursor(46,87);
	GLCD_printf("+", WHITE, LIGHT_BLUE, buttonCursor);
	buttonCursor = Set_Cursor(46,127);
	GLCD_printf("-", WHITE, LIGHT_BLUE, buttonCursor);
	buttonCursor = Set_Cursor(22,167);
	GLCD_printf("Refresh", WHITE, LIGHT_BLUE, buttonCursor);
	buttonCursor = Set_Cursor(34,207);
	GLCD_printf("Back", WHITE, LIGHT_BLUE, buttonCursor);
	
	
	while(1)
	{
		ts_data = GetTS_Fast();
		GLCD_Ellipsoid(75-r,75+r,35-r,35+r,BLACK);
		putarea(91,105,0,239,WHITE);
		
		myItoa(ts_data.xvalue,str,10);
		GLCD_printf_window(str,0x0000, 0xffff, strCursor1, 4);
		myItoa(ts_data.yvalue,str,10);
		GLCD_printf_window(str,0x0000, 0xffff, strCursor2, 4);
		myItoa(ts_data.pvalue,str,10);
		GLCD_printf_window(str,0x0000, 0xffff, strCursor3, 4);
		if(ts_data.pvalue == 1024 && ts_data.xvalue > 105)
		{
			GLCD_Ellipsoid(ts_data.xvalue-r,ts_data.xvalue+r,ts_data.yvalue-r,ts_data.yvalue+r, BLACK);
		}
		else if(r < 15 && ts_data.pvalue == 1024 && ts_data.xvalue > 10 && ts_data.xvalue < 90 && ts_data.yvalue > 80 && ts_data.yvalue < 110)
		{
			r++;
			putarea(75-r,75+r,35-r,35+r,WHITE);
		}
		else if(r > 4 && ts_data.pvalue == 1024 && ts_data.xvalue > 10 && ts_data.xvalue < 90 && ts_data.yvalue > 120 && ts_data.yvalue < 150)
		{
			r--;
			putarea(50,90,20,50,WHITE);
		}
		else if(ts_data.pvalue == 1024 && ts_data.xvalue > 10 && ts_data.xvalue < 90 && ts_data.yvalue > 160 && ts_data.yvalue < 190)
		{
			putarea(106,319,0,239,WHITE);
		}
		else if(ts_data.pvalue == 1024 && ts_data.xvalue > 10 && ts_data.xvalue < 90 && ts_data.yvalue > 200 && ts_data.yvalue < 230)
		{
			return;
		}
	}
}
