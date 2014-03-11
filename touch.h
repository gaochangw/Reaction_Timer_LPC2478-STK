/****************************************************************************
 *
 * Project: LPC-2478-STK
 *
 * Copyright: Ivan Vasilev, Olimex Ltd. All rights reserved.
 *
 * File: touch.h
 * Description: touchscreen include file
 * Developer: Ivan Vasilev, <ivan at l123.org>
 *
 * Last change: $Date: 2008-07-01 14:12:20 +0300 (???????, 01 ??? 2008) $
 * Revision: $Revision: 58 $
 * Id: $Id: iBMapp.c 58 2008-07-01 11:12:20Z Ivan $
 * Author: $Author: Ivan $
 *
 * Revision: By Chang Gao, University of Liverpool, in Feb 2014
 *
 ****************************************************************************/
#include "data_types.h"

#define	X_DEFAULT_RESOLUTION	320
#define	Y_DEFAULT_RESOLUTION	240
#define	P_DEFAULT_RESOLUTION	100

#define	TS_NUM_SAMPLES		2
#define	TS_SETTLING_DELAY	10000

#define	TS_RESOLUTION_BITS	10

#define	TS_X_CHANNEL		ADC_CH_1
#define	TS_Y_CHANNEL		ADC_CH_0

#define TS_X_RATIO    0.3950f	      // For x_coordinate approximation (Gao)
#define TS_Y_RATIO    0.3404f       // For y_coordinate approximation	(Gao)
typedef struct touchscreen_data_t
{
	INT32U	xvalue;
	INT32U	yvalue;
	INT32U	pvalue;
} touchscreen_data;

touchscreen_data	GetTS(void);
void InitTS(touchscreen_data ts_resolution);
void Touch_Test(void);	// Display the coordinates of the touched point on LCD (Gao)
void ts_settling_delay(void);
touchscreen_data	GetTS_Fast(void);
