/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "../LPC24XX.h"		/* LPC23xx/24xx Peripheral Registers	*/
#include "type.h"
#include "../irq.h"
#include "target.h"
#include "timer.h"

volatile DWORD timer0_counter = 0;
volatile DWORD timer1_counter = 0;
/*
* 变量keyvalue保存每次键盘扫描结果
*
* 变量setflag用于表示在时钟设置阶段需要设置的时间单位
* 0：处于显示状态，显示时间或者日期
* 1：设置秒或日
* 2：设置分钟或月
* 3：设置小时或年
*/
volatile BYTE keyvalue = 0,setflag = 0;
/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			
** 						
** Returned value:		None
**
*****************************************************************************/
void delayMs(BYTE timer_num, DWORD delayInMs)
{
  if ( timer_num == 0 )
  {
	/*
	* setup timer #0 for delay
	*/
	T0TCR = 0x02;		/* 复位定时器 */
	T0PR  = 0x00;		/* 预分频设置： TC每PCLK加1 */
	T0MR0 = delayInMs*(Fpclk/1000) - 1;   // 计数值
	T0IR  = 0xff;		/* 中断复位 */
	T0MCR = 0x04;		/* 发生匹配时停止计数 */
	T0TCR = 0x01;		/* 启动定时器 */

	/* wait until delay time has elapsed */
	while (T0TCR & 0x01);   // 当发生匹配，计数器停止，TCR最低位置0，循环结束
  }
  else if ( timer_num == 1 )
  {
	/*
	* setup timer #1 for delay
	*/
	T1TCR = 0x02;		/* reset timer */
	T1PR  = 0x00;		/* set prescaler to zero */
	T1MR0 = delayInMs*(Fpclk/1000) - 1;
	T1IR  = 0xff;		/* reset all interrrupts */
	T1MCR = 0x04;		/* stop timer on match */
	T1TCR = 0x01;		/* start timer */

	/* wait until delay time has elapsed */
	while (T1TCR & 0x01);
  }
  return;
}

/******************************************************************************
** Function name:		Timer0Handler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
__irq __nested __arm void Timer0Handler (void)
{
  T0IR = 1;			/* clear interrupt flag */
  __enable_interrupt();		/* handles nested interrupt */

  timer0_counter++;

  __disable_interrupt();

  VICVectAddr = 0;	/* Acknowledge Interrupt */
}

/******************************************************************************
** Function name:		Timer1Handler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
__irq __nested __arm void Timer1Handler (void)
{
  T1IR = 1;			/* clear interrupt flag */
  __enable_interrupt();			/* handles nested interrupt */


    keyvalue = KeyScan();
    /*if(keyvalue)
    keyvalue -= 4;*/
  __disable_interrupt();

  VICVectAddr = 0;	/* Acknowledge Interrupt */
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( BYTE timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 1;              // 计数器使能
  }
  else
  {
	T1TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( BYTE timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 0;              // 计数器禁止
  }
  else
  {
	T1TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( BYTE timer_num )
{
  DWORD regVal;

  if ( timer_num == 0 )
  {
	regVal = T0TCR;
	regVal |= 0x02;
	T0TCR = regVal;
  }
  else
  {
	regVal = T1TCR;
	regVal |= 0x02;         // 复位。计数器和预分频计数器清0
	T1TCR = regVal;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		true or false, if the interrupt handler can't be
**						installed, return false.
**
******************************************************************************/
DWORD init_timer ( BYTE timer_num, DWORD TimerInterval )
{
  if ( timer_num == 0 )
  {
	timer0_counter = 0;
	T0MR0 = TimerInterval - 1;              // 设置计时初值，计数pclk脉冲个数
	T0MCR = 3;				// 计数器的值与MR值匹配时的动作：发生中断、TC复位
	if ( install_irq( TIMER0_INT, (void *)Timer0Handler, HIGHEST_PRIORITY ) == FALSE )
	{
	  return (FALSE);
	}
	else
	{
	  return (TRUE);
	}
  }
  else if ( timer_num == 1 )
  {
	timer1_counter = 0;
	//T1MR0 = TimerInterval;
        T1MR0 = TimerInterval*(Fpclk/1000) - 1;
	T1MCR = 3;				/* Interrupt and Reset on MR1 */
	if ( install_irq( TIMER1_INT, (void *)Timer1Handler, 0x2 ) == FALSE )
	{
	  return (FALSE);
	}
	else
	{
	  return (TRUE);
	}
  }
  return (FALSE);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
