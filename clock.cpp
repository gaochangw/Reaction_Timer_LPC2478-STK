#include "clock.h"
#include "touch.h"
#include "LPC24XX.h"
#include "low_level_init.h"
#include "clock/type.h"
#include "./rtc.h"



void Init_Timer(void)
{ 
	T1TCR = 0x02; 			/* Reset timer */
  T1PR  = 0x00; 			/* Set prescaler to zero */
  T1MR0 = 0xFFFFFFFF; /* PCLK is 1/4 CCLK */
  T1IR  = 0xFF; 			/* Reset all interrrupts */
  T1MCR = 0x04; 			/* Stop timer on match */
}
void Start_Timer(void)
{
	T1TCR = 0x01; /* Start timer */
}

INT32U Calibrate(void)
{
	INT32U second1 = 0;
	INT32U second2 = 0;
	Init_Timer();
	second1 = RTC_SEC;
	while(RTC_SEC - second1 != 1);
	Start_Timer();
	while(((second2 = RTC_SEC) - second1 - 1) != 15 && ((second2 = RTC_SEC) - second1) != -45);
	return T1TC/15;
}

double Time_Measure(INT32U PCLK_F)
{
	
	double time;
	Init_Timer();
  Start_Timer();
  
	while(GetTS_Fast().pvalue == 0);
	time = T1TC;
	
	return (time/PCLK_F);
}

