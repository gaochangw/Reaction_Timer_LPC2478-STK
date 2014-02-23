#include "data_types.h"
#include "type.h"
#ifndef CLOCK_H
#define CLOCK_H

double Time_Measure(INT32U PCLK_F);
void Init_Timer(void);
void Start_Timer(void);
INT32U Calibrate(void);
#endif
