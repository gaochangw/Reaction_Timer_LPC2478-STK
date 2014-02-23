/*
* clock.c 该文件为时钟设置和扫描函数库
* 
*/
#include "../LPC24XX.H" 
#include "type.h"
#include "clock.h"
#include "timer.h"
#include "rtc.h"


/*void Displaytime(void)
{
  while(keyvalue == 0)    
  {
     if(SPINum%2) // 主程序循环判断ETIN0，决定显示时间或日期 
      {               
        seg_buf[1] = localtime.RTC_Sec%10;//显示时间
        seg_buf[2] = localtime.RTC_Sec/10;
        seg_buf[3] = localtime.RTC_Min%10;
        seg_buf[4] = localtime.RTC_Min/10;
        seg_buf[5] = localtime.RTC_Hour%10;
        seg_buf[6] = localtime.RTC_Hour/10;
      }
      else
      {
        seg_buf[1] = localtime.RTC_Mday%10;//显示日期
        seg_buf[2] = localtime.RTC_Mday/10;
        seg_buf[3] = localtime.RTC_Mon%10;
        seg_buf[4] = localtime.RTC_Mon/10;
        seg_buf[5] = localtime.RTC_Year%10;
        seg_buf[6] = (localtime.RTC_Year%100)/10;
      } 
  }  
}*/

/*void Settime(void)
{
    localtimebuf = RTCGetTime();//读入当前RTC时间值，供设置。
    setflag = 0;

    while(keyvalue != 4)//当键盘按下4键后，将设置的时间写入RTC中
    {
      if(SPINum%2) // 主程序循环判断ETIN0，决定显示时间或日期 
      {               
        seg_buf[1] = localtimebuf.RTC_Sec%10;//显示时间
        seg_buf[2] = localtimebuf.RTC_Sec/10;
        seg_buf[3] = localtimebuf.RTC_Min%10;
        seg_buf[4] = localtimebuf.RTC_Min/10;
        seg_buf[5] = localtimebuf.RTC_Hour%10;
        seg_buf[6] = localtimebuf.RTC_Hour/10;
      }
      else
      {
        seg_buf[1] = localtimebuf.RTC_Mday%10;//显示日期
        seg_buf[2] = localtimebuf.RTC_Mday/10;
        seg_buf[3] = localtimebuf.RTC_Mon%10;
        seg_buf[4] = localtimebuf.RTC_Mon/10;
        seg_buf[5] = localtimebuf.RTC_Year%10;
        seg_buf[6] = (localtimebuf.RTC_Year%100)/10;
      }
      if(keyvalue == 1)
      {
        setflag++;
        setflag %= 4;
        if(setflag == 0)
          setflag = 1;
      }
      switch(setflag)
        {
        case 1:
          if(SPINum%2)
          {    if(keyvalue == 2)
               {
                 localtimebuf.RTC_Sec++;
                 localtimebuf.RTC_Sec %= 60;
               }
              if(keyvalue == 3)
               {
                  localtimebuf.RTC_Sec--;/**/
                  if(localtimebuf.RTC_Sec == -1)
                     localtimebuf.RTC_Sec = 59;
               }
          }
          else
          {    if(keyvalue == 2)
               {
                 localtimebuf.RTC_Mday++;
                 localtimebuf.RTC_Mday %= 31;
               }
              if(keyvalue == 3)
               {
                  localtimebuf.RTC_Mday--;/**/
                  if(localtimebuf.RTC_Mday == 0)
                     localtimebuf.RTC_Mday = 31;
               }
          }
          break;
        case 2:
          if(SPINum%2)
          {   if(keyvalue == 2)
                {
                    localtimebuf.RTC_Min++;
                    localtimebuf.RTC_Min %= 60;
                }
              if(keyvalue == 3)
              {
                    localtimebuf.RTC_Min--;/**/
                    if(localtimebuf.RTC_Min == -1)
                       localtimebuf.RTC_Min = 59;
              }
          }
          else
          {  if(keyvalue == 2)
                {
                    localtimebuf.RTC_Mon++;
                    localtimebuf.RTC_Mon %= 13;
                }
              if(keyvalue == 3)
              {
                    localtimebuf.RTC_Mon--;/**/
                    if(localtimebuf.RTC_Mon == 0)
                       localtimebuf.RTC_Mon = 12;
              }
          }
          break;
        case 3:
          if(SPINum%2)
          {
              if(keyvalue == 2)
                {
                    localtimebuf.RTC_Hour++;
                    localtimebuf.RTC_Hour %= 24;
                }
               if(keyvalue == 3)
               {
                    localtimebuf.RTC_Hour--;/**/
                    if(localtimebuf.RTC_Hour == -1)
                       localtimebuf.RTC_Hour = 23;
               }
          }
        default:
          break;
        }

    delayMs(0,200);
    }
    RTCSetTime(localtimebuf);
    RTCInit();
    RTCStart();
    setflag = 0;*/
}
/*****************************************************************************
**                            End Of File
*****************************************************************************/
