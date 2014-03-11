/*****************************************************************************
 *   rtc.c:  Realtime clock C file for NXP LPC23xx/34xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.12  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include "../LPC24XX.H"                        /* LPC23xx/24xx definitions */
#include "type.h"
#include "../irq.h"
#include "rtc.h"
#include "target.h"
#include "timer.h"

volatile DWORD rtc_alarm_on = 0;
volatile RTCTime localtime = {0,31,16,1,12,2008,0,0};
RTCTime localtimebuf;
/*****************************************************************************
** Function name:		RTCHandler
**
** Descriptions:		RTC interrupt handler, it executes based on the
**				the alarm setting
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/


/*****************************************************************************
** Function name:		RTCInit
**
** Descriptions:		Initialize RTC timer
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
BOOL RTCInit( void )
{
	int f;
  rtc_alarm_on = 0;

  /*--- Initialize registers ---*/
  RTC_AMR = 0;          // 报警屏蔽
  RTC_CIIR = 0x1;         // 设置RTC产生秒增量中断，在中断服务程序中读取当前
                          //时钟信息。
  RTC_CCR = 0x0;          // 使能复位

  /*if ( install_irq( RTC_INT, (void *)RTCHandler,HIGHEST_PRIORITY ) == FALSE )
	{
	  return (FALSE);
	}*/
	//f = Fpclk;
  //RTC_PREINT = Fpclk/32768 - 1;   //预分频
  //RTC_PREFRAC = Fpclk % 32768;

  return TRUE;
}

/*****************************************************************************
** Function name:		RTCStart
**
** Descriptions:		Start RTC timer
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void RTCStart( void )
{
  /*--- Start RTC counters ---*/
  RTC_CCR |= CCR_CLKEN;
  RTC_ILR = ILR_RTCCIF;         // 增量中断模式
  return;
}

/*****************************************************************************
** Function name:		RTCStop
**
** Descriptions:		Stop RTC timer
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void RTCStop( void )
{
  /*--- Stop RTC counters ---*/
  RTC_CCR &= ~CCR_CLKEN;
  return;
}

/*****************************************************************************
** Function name:		RTC_CTCReset
**
** Descriptions:		Reset RTC clock tick counter
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void RTC_CTCReset( void )
{
  /*--- Reset CTC ---*/
  RTC_CCR |= CCR_CTCRST;
  return;
}

/*****************************************************************************
** Function name:		RTCSetTime
**
** Descriptions:		Setup RTC timer value
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void RTCSetTime( RTCTime Time )
{
  RTCStop();//在设置RTC前应该先停止其运行    
  RTC_CTCReset();  
  RTC_SEC = Time.RTC_Sec;
  RTC_MIN = Time.RTC_Min;
  RTC_HOUR = Time.RTC_Hour;
  RTC_DOM = Time.RTC_Mday;
  RTC_DOW = Time.RTC_Wday;
  RTC_DOY = Time.RTC_Yday;
  RTC_MONTH = Time.RTC_Mon;
  RTC_YEAR = Time.RTC_Year;
  
  return;
}

/*****************************************************************************
** Function name:		RTCSetAlarm
**
** Descriptions:		Initialize RTC timer
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void RTCSetAlarm( RTCTime Alarm )
{
  RTC_ALSEC = Alarm.RTC_Sec;
  RTC_ALMIN = Alarm.RTC_Min;
  RTC_ALHOUR = Alarm.RTC_Hour;
  RTC_ALDOM = Alarm.RTC_Mday;
  RTC_ALDOW = Alarm.RTC_Wday;
  RTC_ALDOY = Alarm.RTC_Yday;
  RTC_ALMON = Alarm.RTC_Mon;
  RTC_ALYEAR = Alarm.RTC_Year;
  return;
}

/*****************************************************************************
** Function name:		RTCGetTime
**
** Descriptions:		Get RTC timer value
**
** parameters:			None
** Returned value:		The data structure of the RTC time table
**
*****************************************************************************/
RTCTime RTCGetTime( void )
{
  RTCTime LocalTime;

  LocalTime.RTC_Sec = RTC_SEC;
  LocalTime.RTC_Min = RTC_MIN;
  LocalTime.RTC_Hour = RTC_HOUR;
  LocalTime.RTC_Mday = RTC_DOM;
  LocalTime.RTC_Wday = RTC_DOW;
  LocalTime.RTC_Yday = RTC_DOY;
  LocalTime.RTC_Mon = RTC_MONTH;
  LocalTime.RTC_Year = RTC_YEAR;
  return ( LocalTime );
}

/*****************************************************************************
** Function name:		RTCSetAlarmMask
**
** Descriptions:		Set RTC timer alarm mask
**
** parameters:			Alarm mask setting
** Returned value:		None
**
*****************************************************************************/
void RTCSetAlarmMask( DWORD AlarmMask )
{
  /*--- Set alarm mask ---*/
  RTC_AMR = AlarmMask;
  return;
}

/*****************************************************************************
**                            End Of File
******************************************************************************/

