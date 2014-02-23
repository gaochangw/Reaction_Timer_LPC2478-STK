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
* ����keyvalue����ÿ�μ���ɨ����
*
* ����setflag���ڱ�ʾ��ʱ�����ý׶���Ҫ���õ�ʱ�䵥λ
* 0��������ʾ״̬����ʾʱ���������
* 1�����������
* 2�����÷��ӻ���
* 3������Сʱ����
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
	T0TCR = 0x02;		/* ��λ��ʱ�� */
	T0PR  = 0x00;		/* Ԥ��Ƶ���ã� TCÿPCLK��1 */
	T0MR0 = delayInMs*(Fpclk/1000) - 1;   // ����ֵ
	T0IR  = 0xff;		/* �жϸ�λ */
	T0MCR = 0x04;		/* ����ƥ��ʱֹͣ���� */
	T0TCR = 0x01;		/* ������ʱ�� */

	/* wait until delay time has elapsed */
	while (T0TCR & 0x01);   // ������ƥ�䣬������ֹͣ��TCR���λ��0��ѭ������
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
	T0TCR = 1;              // ������ʹ��
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
	T0TCR = 0;              // ��������ֹ
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
	regVal |= 0x02;         // ��λ����������Ԥ��Ƶ��������0
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
	T0MR0 = TimerInterval - 1;              // ���ü�ʱ��ֵ������pclk�������
	T0MCR = 3;				// ��������ֵ��MRֵƥ��ʱ�Ķ����������жϡ�TC��λ
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
