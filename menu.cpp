#include "menu.h"
#include "low_level_init.h"
#include "lcd_draw.h"
#include "lcd_text.h"
#include "clock.h"
#include "touch.h"
#include "clock/rtc.h"
#include "LPC24xx.h"
#include "gif_stream6.h"
#include "liverpool_logo.h"
#include <stdlib.h>
#include <string.h>


static INT32U PCLK_F = 28800000;

DWORD GetWeekDay(DWORD Day, DWORD Month, DWORD Year)
{
	if(Month<3)
		Month += 12;
	return (Day+2*Month+3*(Month+1)/5+Year+Year/4-Year/100+Year/400+1)%7;
}
void Time_Display(INT16S FT_Color, INT16S BG_Color)
{
	int digYear   = RTC_YEAR;
	int digMonth  = RTC_MONTH;
	int digDay    = RTC_DOM;
	int digHour   = RTC_HOUR;
	int digMinute = RTC_MIN;
	int digSecond = RTC_SEC;
	int digWday   = RTC_DOW;
	
	char strYear[5] = {0};
	char strMonth[3] = {0};
	char strDay[3] = {0};
	char strHour[3] = {0};
	char strMinute[3] = {0};
	char strSecond[3] = {0};
	char strWday[4]   = {0};
	Cursor TimeCursor;
	
	myItoa(digYear,strYear,10);
	strDay[0] = digDay/10 + 48;
	strDay[1] = digDay%10 + 48;
	strHour[0] = digHour/10 + 48;
	strHour[1] = digHour%10 + 48;
	strMinute[0] = digMinute/10 + 48;
	strMinute[1] = digMinute%10 + 48;
	strSecond[0] = digSecond/10 + 48;
	strSecond[1] = digSecond%10 + 48;
	
	switch(digMonth)
	{
		case 1 : strcpy(strMonth,"Jan"); break;
		case 2 : strcpy(strMonth,"Feb"); break;
		case 3 : strcpy(strMonth,"Mar"); break;
		case 4 : strcpy(strMonth,"Apr"); break;
		case 5 : strcpy(strMonth,"May"); break;
		case 6 : strcpy(strMonth,"Jun"); break;
		case 7 : strcpy(strMonth,"Jul"); break;
		case 8 : strcpy(strMonth,"Aug"); break;
		case 9 : strcpy(strMonth,"Sep"); break;
		case 10: strcpy(strMonth,"Oct"); break;
		case 11: strcpy(strMonth,"Nov"); break;
		case 12: strcpy(strMonth,"Dec"); break;
	}
	
	switch(digWday)
	{
		case 1 : strcpy(strWday,"Mon"); break;
		case 2 : strcpy(strWday,"Tue"); break;
		case 3 : strcpy(strWday,"Wed"); break;
		case 4 : strcpy(strWday,"Thu"); break;
		case 5 : strcpy(strWday,"Fri"); break;
		case 6 : strcpy(strWday,"Sat"); break;
		case 0 : strcpy(strWday,"Sun"); break;
	}
	
	
	
	TimeCursor = Set_Cursor(0, 0);
	GLCD_printf(strWday, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 32, TimeCursor.yValue);
	GLCD_printf(strDay, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 24, TimeCursor.yValue);
	GLCD_printf(strMonth, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 32, TimeCursor.yValue);
	GLCD_printf(strYear, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 40, TimeCursor.yValue);
	GLCD_printf(strHour, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 16, TimeCursor.yValue);
	GLCD_printf(":", FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 8, TimeCursor.yValue);
	GLCD_printf(strMinute, FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 16, TimeCursor.yValue);
	GLCD_printf(":", FT_Color, BG_Color, TimeCursor);
	TimeCursor = Set_Cursor(TimeCursor.xValue + 8, TimeCursor.yValue);
	GLCD_printf(strSecond, FT_Color, BG_Color, TimeCursor);
	
}

void Logo(void)
{
	Cursor picCursor;
	picCursor = Set_Cursor(160, 55);
	PutPicture(gImage_liverpool_logo, 280, 50, picCursor);
}


BOOL Start_Animation(void)
{
	Cursor picCursor, strCursor;
	
	picCursor = Set_Cursor(155, 110);
	strCursor = Set_Cursor(92, 180);
	
	Lcd_ClearScr(320,240,0xffff);
	GLCD_printf("Press to Continue", 0x0000, 0xFFFF, strCursor);
	
	while(1)
	{
	PutPicture(gImage_IMG00000, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00001, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00002, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00003, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00004, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00005, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00006, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00007, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00008, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00009, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00010, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	PutPicture(gImage_IMG00011, 90, 90, picCursor);
	delayMs(300);
	if(GetTS().pvalue == 1024)
			return 0;
	}
}

INT8U Menu_Single(void)
{
	#define ARRAY_OFFSET 25
	
	INT8U i = 0;
	INT8U current_rand = 0, saved_rand = 0;
	Cursor strCursor;
	float t = 0.0;
	char str_time[10] = {0};
	char index[2] = {0};
	float total_time = 0.0;
	float mean_time = 0.0;
	
	
	
	strCursor = Set_Cursor(0, 0);
	Lcd_ClearScr(320,240,0xffff);
  GLCD_printf(" Touch the screen when patterns change! ", 0xffff, RED, strCursor);
	
	
	
	for(i = 0; i != 5; ++i)
	{
		
	  delayMs(1000 + (rand() % 9000));
		srand(RTC_SEC);
		while((current_rand = rand() % 25) == saved_rand);
		saved_rand = current_rand;
		GLCD_RandomPattern(current_rand);
		
		t = Time_Measure(PCLK_F);
		total_time += t;
		
		ftoa(str_time, t, 5);
		strCursor = Set_Cursor(30, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf("Time ", BLACK, WHITE, strCursor);
		myItoa(i + 1, index, 10);
		strCursor = Set_Cursor(70, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(index, BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(78, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(": ", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(94, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf_window(str_time, BLACK, WHITE, strCursor, 7);
		strCursor = Set_Cursor(150, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(" s", BLACK, WHITE, strCursor);
	}
	
	mean_time = total_time / 5.0;
	ftoa(str_time, mean_time, 5); // "Mean Reaction Time: 0.22222 s"
	
	strCursor = Set_Cursor(44, 200);
	GLCD_printf("Mean Reaction Time: ", RED, WHITE, strCursor);
	strCursor = Set_Cursor(204, 200);
	GLCD_printf_window(str_time, RED, WHITE, strCursor, 7);
	strCursor = Set_Cursor(260, 200);
	GLCD_printf(" s", RED, WHITE, strCursor);
	
	delayMs(1000);
	while(1)
		{
			if(GetTS().pvalue == 1024)
				return 1;
		}	
}

INT8U Game(void)
{
	Cursor strCursor;
	float t = 0.0;
	char time[10] = {0};

	strCursor = Set_Cursor(20, 30);
	Lcd_ClearScr(320,240,0xffff);
  GLCD_printf("Touch the screen when you see image", 0xffff, BLUE, strCursor);
	srand(256);
	delayMs(1000 + (rand() % 9000));
	putarea(100,220,50,100,0x0000);
	t = Time_Measure(PCLK_F);
	ftoa(time, t, 5);
	GLCD_printf(time, 0xffff, 0x1f, strCursor);
	
	delayMs(500);
	
	while(1)
	{
		if(GetTS().pvalue == 1024)
			return 1;
	}	
}


void Menu_Option(void)
{
	#define DATE_X 15
	#define DATE_Y 60
	#define TIME_X 30
	#define TIME_Y 110
	#define KB_X 160
	#define KB_Y 25
	#define R 10
	
	Cursor strCursor;
	Cursor cDD1,cDD2,cMM1,cMM2,cYY1,cYY2,cYY3,cYY4,cHR1,cHR2,cMN1,cMN2,cSE1,cSE2;
	RTCTime Time;
	char DD[3] = {0},MM[3] = {0},YY[5] = {0},HR[3] = {0},MN[3] = {0},SE[3] = {0};
		
	touchscreen_data TD;
	INT8U index = 0, del_t = 0;
	char num[2] = {0};
	
	/* GUI */
	Lcd_ClearScr(320,240,WHITE);
	putarea(DATE_X,DATE_X+10,DATE_Y,DATE_Y+20,LIGHT_BLUE);	// Day
	putarea(DATE_X+15,DATE_X+25,DATE_Y,DATE_Y+20,LIGHT_BLUE);
	putarea(DATE_X+35,DATE_X+45,DATE_Y,DATE_Y+20,LIGHT_BLUE);	// Month
	putarea(DATE_X+50,DATE_X+60,DATE_Y,DATE_Y+20,LIGHT_BLUE);
	putarea(DATE_X+70,DATE_X+80,DATE_Y,DATE_Y+20,LIGHT_BLUE);	// Year
	putarea(DATE_X+85,DATE_X+95,DATE_Y,DATE_Y+20,LIGHT_BLUE);
	putarea(DATE_X+100,DATE_X+110,DATE_Y,DATE_Y+20,LIGHT_BLUE);
	putarea(DATE_X+115,DATE_X+125,DATE_Y,DATE_Y+20,LIGHT_BLUE);
	
	strCursor = Set_Cursor(DATE_X+1,DATE_Y-18);
	GLCD_printf("D", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+16,DATE_Y-18);
	GLCD_printf("D", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+36,DATE_Y-18);
	GLCD_printf("M", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+51,DATE_Y-18);
	GLCD_printf("M", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+71,DATE_Y-18);
	GLCD_printf("Y", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+86,DATE_Y-18);
	GLCD_printf("Y", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+101,DATE_Y-18);
	GLCD_printf("Y", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+116,DATE_Y-18);
	GLCD_printf("Y", BLACK,WHITE,strCursor);
	
	putarea(TIME_X,TIME_X+10,TIME_Y,TIME_Y+20,LIGHT_BLUE);	// Hour
	putarea(TIME_X+15,TIME_X+25,TIME_Y,TIME_Y+20,LIGHT_BLUE);
	putarea(TIME_X+35,TIME_X+45,TIME_Y,TIME_Y+20,LIGHT_BLUE);	// Minute
	putarea(TIME_X+50,TIME_X+60,TIME_Y,TIME_Y+20,LIGHT_BLUE);
	putarea(TIME_X+70,TIME_X+80,TIME_Y,TIME_Y+20,LIGHT_BLUE);	// Second
	putarea(TIME_X+85,TIME_X+95,TIME_Y,TIME_Y+20,LIGHT_BLUE);
	
	strCursor = Set_Cursor(TIME_X+1,TIME_Y-18);
	GLCD_printf("h", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+16,TIME_Y-18);
	GLCD_printf("h", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+36,TIME_Y-18);
	GLCD_printf("m", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+51,TIME_Y-18);
	GLCD_printf("m", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+71,TIME_Y-18);
	GLCD_printf("s", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+86,TIME_Y-18);
	GLCD_printf("s", BLACK,WHITE,strCursor);
	
	
	cDD1 = Set_Cursor(DATE_X+1,DATE_Y+2);
	cDD2 = Set_Cursor(DATE_X+16,DATE_Y+2);
	cMM1 = Set_Cursor(DATE_X+36,DATE_Y+2);
	cMM2 = Set_Cursor(DATE_X+51,DATE_Y+2);
	cYY1 = Set_Cursor(DATE_X+71,DATE_Y+2);
	cYY2 = Set_Cursor(DATE_X+86,DATE_Y+2);
	cYY3 = Set_Cursor(DATE_X+101,DATE_Y+2);
	cYY4 = Set_Cursor(DATE_X+116,DATE_Y+2);
	cHR1 = Set_Cursor(TIME_X+1,TIME_Y+2);
	cHR2 = Set_Cursor(TIME_X+16,TIME_Y+2);
	cMN1 = Set_Cursor(TIME_X+36,TIME_Y+2);
	cMN2 = Set_Cursor(TIME_X+51,TIME_Y+2);
	cSE1 = Set_Cursor(TIME_X+71,TIME_Y+2);
	cSE2 = Set_Cursor(TIME_X+86,TIME_Y+2);
	
	
	strCursor = Set_Cursor(DATE_X+27, DATE_Y+2);
	GLCD_printf("/", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(DATE_X+62, DATE_Y+2);
	GLCD_printf("/", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+27, TIME_Y+2);
	GLCD_printf(":", BLACK,WHITE,strCursor);
	strCursor = Set_Cursor(TIME_X+62, TIME_Y+2);
	GLCD_printf(":", BLACK,WHITE,strCursor);
	
	
	
	GLCD_RoundRect(KB_X,KB_X+40,KB_Y,KB_Y+40,R,BLACK);					// Button: 1
	GLCD_RoundRect(KB_X+50,KB_X+90,KB_Y,KB_Y+40,R,BLACK);				// Button: 2
	GLCD_RoundRect(KB_X+100,KB_X+140,KB_Y,KB_Y+40,R,BLACK);			// Button: 3
	
	GLCD_RoundRect(KB_X,KB_X+40,KB_Y+50,KB_Y+90,R,BLACK);				// Button: 4
	GLCD_RoundRect(KB_X+50,KB_X+90,KB_Y+50,KB_Y+90,R,BLACK);		// Button: 5
	GLCD_RoundRect(KB_X+100,KB_X+140,KB_Y+50,KB_Y+90,R,BLACK);	// Button: 6
	
	GLCD_RoundRect(KB_X,KB_X+40,KB_Y+100,KB_Y+140,R,BLACK);			// Button: 7
	GLCD_RoundRect(KB_X+50,KB_X+90,KB_Y+100,KB_Y+140,R,BLACK);	// Button: 8
	GLCD_RoundRect(KB_X+100,KB_X+140,KB_Y+100,KB_Y+140,R,BLACK);// Button: 9
	
	GLCD_RoundRect(KB_X,KB_X+40,KB_Y+150,KB_Y+190,R,BLACK);			// Button: OK
	GLCD_RoundRect(KB_X+50,KB_X+90,KB_Y+150,KB_Y+190,R,BLACK);	// Button: 0
	GLCD_RoundRect(KB_X+100,KB_X+140,KB_Y+150,KB_Y+190,R,BLACK);// Button: DEL
	
	GLCD_RoundRect(TIME_X,TIME_X+95,KB_Y+150,KB_Y+190,R,RED);// Button: EXIT
	
	strCursor = Set_Cursor(KB_X+16, KB_Y+12);
	GLCD_printf("1", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+66, KB_Y+12);
	GLCD_printf("2", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+116, KB_Y+12);
	GLCD_printf("3", WHITE,BLACK,strCursor);
	
	strCursor = Set_Cursor(KB_X+16, KB_Y+62);
	GLCD_printf("4", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+66, KB_Y+62);
	GLCD_printf("5", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+116, KB_Y+62);
	GLCD_printf("6", WHITE,BLACK,strCursor);
	
	strCursor = Set_Cursor(KB_X+16, KB_Y+112);
	GLCD_printf("7", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+66, KB_Y+112);
	GLCD_printf("8", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+116, KB_Y+112);
	GLCD_printf("9", WHITE,BLACK,strCursor);
	
	strCursor = Set_Cursor(KB_X+13, KB_Y+162);
	GLCD_printf("OK", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+66, KB_Y+162);
	GLCD_printf("0", WHITE,BLACK,strCursor);
	strCursor = Set_Cursor(KB_X+109, KB_Y+162);
	GLCD_printf("DEL", WHITE,BLACK,strCursor);
	
	strCursor = Set_Cursor(TIME_X+32, KB_Y+162);
	GLCD_printf("EXIT", WHITE,RED,strCursor);
	
	while(1)
	{
		delayMs(500);
		while(1)
		{
			TD = GetTS();
			if(TD.pvalue != 0 && TD.xvalue > KB_X && TD.xvalue < KB_X+40 && TD.yvalue > KB_Y && TD.yvalue < KB_Y+40)	// Button: 1
			{
				num[0] = '1';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+50 && TD.xvalue < KB_X+90 && TD.yvalue > KB_Y && TD.yvalue < KB_Y+40)	// Button: 2
			{
				num[0] = '2';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+100 && TD.xvalue < KB_X+140 && TD.yvalue > KB_Y && TD.yvalue < KB_Y+40)	// Button: 3
			{
				num[0] = '3';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X && TD.xvalue < KB_X+40 && TD.yvalue > KB_Y+50 && TD.yvalue < KB_Y+90)	// Button: 4
			{
				num[0] = '4';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+50 && TD.xvalue < KB_X+90 && TD.yvalue > KB_Y+50 && TD.yvalue < KB_Y+90)	// Button: 5
			{
				num[0] = '5';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+100 && TD.xvalue < KB_X+140 && TD.yvalue > KB_Y+50 && TD.yvalue < KB_Y+90)	// Button: 6
			{
				num[0] = '6';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X && TD.xvalue < KB_X+40 && TD.yvalue > KB_Y+100 && TD.yvalue < KB_Y+140)	// Button: 7
			{
				num[0] = '7';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+50 && TD.xvalue < KB_X+90 && TD.yvalue > KB_Y+100 && TD.yvalue < KB_Y+140)	// Button: 8
			{
				num[0] = '8';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+100 && TD.xvalue < KB_X+140 && TD.yvalue > KB_Y+100 && TD.yvalue < KB_Y+140)	// Button: 9
			{
				num[0] = '9';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X && TD.xvalue < KB_X+40 && TD.yvalue > KB_Y+150 && TD.yvalue < KB_Y+190)	// Button: OK
			{
				Time.RTC_Mday = atoi(DD);
				Time.RTC_Mon = atoi(MM);
				Time.RTC_Year = atoi(YY);
				Time.RTC_Hour = atoi(HR);
				Time.RTC_Min = atoi(MN);
				Time.RTC_Sec = atoi(SE);
				Time.RTC_Wday = GetWeekDay(Time.RTC_Mday,Time.RTC_Mon,Time.RTC_Year);
				RTCSetTime(Time);
				RTCInit();
				RTCStart();
				return;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+50 && TD.xvalue < KB_X+90 && TD.yvalue > KB_Y+150 && TD.yvalue < KB_Y+190)	// Button: 0
			{
				num[0] = '0';
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > KB_X+100 && TD.xvalue < KB_X+140 && TD.yvalue > KB_Y+150 && TD.yvalue < KB_Y+190)	// Button: DEL
			{
				del_t = 1;
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > TIME_X && TD.xvalue < TIME_X+95 && TD.yvalue > KB_Y+150 && TD.yvalue < KB_Y+190)	// Button: DEL
			{
				return;
			}
		}
		
		
		switch(index)
		{
			case 0:
			{
				if(!del_t)
				{
					DD[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cDD1);
					index++;
				}
				else
				{
					del_t = 0;
				}
				break;
			}
			case 1:
			{
				if(!del_t)
				{
					DD[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cDD2);
					index++;
				}
				else
				{
					DD[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cDD1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 2:
			{
				if(!del_t)
				{
					MM[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cMM1);
					index++;
				}
				else
				{
					DD[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cDD2);
					index--;
					del_t = 0;
				}
				break;
			}
			case 3:
			{
				if(!del_t)
				{
					MM[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cMM2);
					index++;
				}
				else
				{
					MM[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cMM1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 4:
			{
				if(!del_t)
				{
					YY[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cYY1);
					index++;
				}
				else
				{
					MM[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cMM2);
					index--;
					del_t = 0;
				}
				break;
			}
			case 5:
			{
				if(!del_t)
				{
					YY[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cYY2);
					index++;
				}
				else
				{
					YY[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cYY1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 6:
			{
				if(!del_t)
				{
					YY[2] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cYY3);
					index++;
				}
				else
				{
					YY[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cYY2);
					index--;
					del_t = 0;
				}
				break;
			}
			case 7:
			{
				if(!del_t)
				{
					YY[3] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cYY4);
					index++;
				}
				else
				{
					YY[2] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cYY3);
					index--;
					del_t = 0;
				}
				break;
			}
			case 8:
			{
				if(!del_t)
				{
					HR[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cHR1);
					index++;
				}
				else
				{
					YY[3] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cYY4);
					index--;
					del_t = 0;
				}
				break;
			}
			case 9:
			{
				if(!del_t)
				{
					HR[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cHR2);
					index++;
				}
				else
				{
					HR[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cHR1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 10:
			{
				if(!del_t)
				{
					MN[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cMN1);
					index++;
				}
				else
				{
					HR[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cHR2);
					index--;
					del_t = 0;
				}
				break;
			}
			case 11:
			{
				if(!del_t)
				{
					MN[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cMN2);
					index++;
				}
				else
				{
					MN[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cMN1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 12:
			{
				if(!del_t)
				{
					SE[0] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cSE1);
					index++;
				}
				else
				{
					MN[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cMN2);
					index--;
					del_t = 0;
				}
				break;
			}
			case 13:
			{
				if(!del_t)
				{
					SE[1] = num[0];
					GLCD_printf(num,WHITE,LIGHT_BLUE,cSE2);
					index++;
				}
				else
				{
					SE[0] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cSE1);
					index--;
					del_t = 0;
				}
				break;
			}
			case 14:
			{
				if(!del_t)
				{
					break;
				}
				else
				{
					SE[1] = '0';
					GLCD_printf(" ",WHITE,LIGHT_BLUE,cSE2);
					index--;
					del_t = 0;
				}
				break;
			}
		}
	}
}

/***************************
main menu
***************************/
void Menu_Main(void)
{
	Cursor strCursor;
	touchscreen_data TD;
	Start_Animation();
	
	while(1)
	{
		/* Draw patterns */
		Lcd_ClearScr(320,240,WHITE);
		putarea(0, 278, 0, 16, BLACK);
		putarea(279, 319, 0, 16, RED);
		strCursor = Set_Cursor(40,138);
		GLCD_Ellipsoid(20, 100, 105, 185, BLACK);
		GLCD_printf("START", WHITE, BLACK, strCursor);
		strCursor = Set_Cursor(142,140);
		GLCD_printf("Super Reaction Timer", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(7,220);
		GLCD_printf("Authors: C.Gao, Z.Y.Fu, H.Zhang, T.Zhu", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(279,0);
		GLCD_printf("SETUP", WHITE, RED, strCursor);
		Logo();
	
		/* Detect touch */
		while(1)
		{
			Time_Display(WHITE, BLACK);
			TD = GetTS();
			if(TD.pvalue != 0 && TD.xvalue > 20 && TD.xvalue < 100 && TD.yvalue > 105 && TD.yvalue < 185)
			{
				delayMs(500);
				Menu_GameMode();
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > 270 && TD.xvalue < 320 && TD.yvalue > 0 && TD.yvalue < 20)
			{
				delayMs(500);
				Menu_Option();
				break;
			}
		}
	}
}

/*****************************
player menu
******************************/

INT8U Menu_Player(void)
{
	Cursor strCursor;
	touchscreen_data TD;

	/* Draw patterns */
	Lcd_ClearScr(320,240,WHITE);
	
	GLCD_Ellipsoid(135,185,95,145,RED);	// Back button
	GLCD_RoundRect(40,140,40,100,10,BLACK);	// Top left
	GLCD_RoundRect(40,140,140,200,10,BLACK);	// Bottom left
	GLCD_RoundRect(180,280,40,100,10,BLACK);	// Top right
	GLCD_RoundRect(180,280,140,200,10,BLACK);// Bottom right
	
	strCursor = Set_Cursor(145,112);
	GLCD_printf("Back", WHITE, RED, strCursor);
	strCursor = Set_Cursor(54,62);
	GLCD_printf("2 Players", WHITE, BLACK, strCursor);
	strCursor = Set_Cursor(194,62);
	GLCD_printf("3 Players", WHITE, BLACK, strCursor);
	strCursor = Set_Cursor(54,162);
	GLCD_printf("4 Players", WHITE, BLACK, strCursor);
	strCursor = Set_Cursor(194,162);
	GLCD_printf("5 Players", WHITE, BLACK, strCursor);
	
	delayMs(500);
	/* Detect touch */
	while(1)
	{
		TD = GetTS();
		if(TD.pvalue != 0 && TD.xvalue > 135 && TD.xvalue < 185 && TD.yvalue > 95 && TD.yvalue < 145)
			return 0;
		if(TD.pvalue != 0 && TD.xvalue > 40 && TD.xvalue < 140 && TD.yvalue > 40 && TD.yvalue < 100)
			return 2;
		if(TD.pvalue != 0 && TD.xvalue > 40 && TD.xvalue < 140 && TD.yvalue > 140 && TD.yvalue < 200)
			return 4;
		if(TD.pvalue != 0 && TD.xvalue > 180 && TD.xvalue < 280 && TD.yvalue > 40 && TD.yvalue < 100)
			return 3;
		if(TD.pvalue != 0 && TD.xvalue > 180 && TD.xvalue < 280 && TD.yvalue > 140 && TD.yvalue < 200)
			return 5;
	}
}


void Menu_GameMode(void)
{
	Cursor strCursor;
	touchscreen_data TD;
	
	/* Detect touch */
	while(1)
	{
		/* Draw Patterns */
		Lcd_ClearScr(320,240,0xffff);
		putarea(0, 319, 0, 16, BLACK);
		
		//putarea(80,240,20,60,LIGHT_BLUE);
		GLCD_Ellipsoid(135,185,105,155,RED);	// Back button
		GLCD_RoundRect(40,140,50,110,10,LIGHT_BLUE);	// Top left
		GLCD_RoundRect(40,140,150,210,10,LIGHT_BLUE);	// Bottom left
		GLCD_RoundRect(180,280,50,110,10,LIGHT_BLUE);	// Top right
		GLCD_RoundRect(180,280,150,210,10,LIGHT_BLUE);// Bottom right
	
		strCursor = Set_Cursor(145,122);
		GLCD_printf("Exit", WHITE, RED, strCursor);
		strCursor = Set_Cursor(66,72);
		GLCD_printf("Single", WHITE, LIGHT_BLUE, strCursor);
		strCursor = Set_Cursor(198,72);
		GLCD_printf("Multiple", WHITE, LIGHT_BLUE, strCursor);
		strCursor = Set_Cursor(54,172);
		GLCD_printf("Calibrate", WHITE, LIGHT_BLUE, strCursor);
		strCursor = Set_Cursor(190,172);
		GLCD_printf("Touch Demo", WHITE, LIGHT_BLUE, strCursor);
		
		while(1)
		{
			
			Time_Display(WHITE, BLACK);
			TD = GetTS();
			if(TD.pvalue != 0 && TD.xvalue > 145 && TD.xvalue < 175 && TD.yvalue > 115 && TD.yvalue < 145)     /*Back*/     
			{
				return;
			}
			else if(TD.pvalue != 0 && TD.xvalue > 40 && TD.xvalue < 140 && TD.yvalue > 50 && TD.yvalue < 110)    /*Single player*/
			{
				Menu_Single();
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > 180 && TD.xvalue < 280 && TD.yvalue > 50 && TD.yvalue < 110)  /*Multiple Players*/
			{
				Menu_Multiple(Menu_Player());
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > 40 && TD.xvalue < 140 && TD.yvalue > 150 && TD.yvalue < 210)  /*Menu_Calibrate*/
			{
				Menu_Calibrate();
				break;
			}
			else if(TD.pvalue != 0 && TD.xvalue > 180 && TD.xvalue < 280 && TD.yvalue > 150 && TD.yvalue < 210)  /*Menu_Calibrate*/
			{
				Touch_Test();
				break;
			}
		}
		
	}
}



INT8U Ranking(float* Player_Time,char* Player_Time_Order,INT8U k)
{
	float n = 0.0;
	int i = 0,j = 0;
	char m;
	char index[2] = {0};
	Cursor strCursor;
	char str_time[10] = {0};
	char str[2] = {0};
  
 	for(i=k-1;i>=0;--i)
	{
		for(j=k-1;j>=0;--j)
		{
			if(Player_Time[j]<Player_Time[j-1])
			{
				n = Player_Time[j];
				Player_Time[j] = Player_Time[j-1];
				Player_Time[j-1] = n;
				m = Player_Time_Order[j];
				Player_Time_Order[j] = Player_Time_Order[j-1];
				Player_Time_Order[j-1] = m;
			}
		}
	}
	Lcd_ClearScr(320,240,WHITE);
	strCursor = Set_Cursor(144, 20);
	GLCD_printf("Rank", RED, WHITE, strCursor);
	for(i=0;i<k;++i)
	{
		strCursor = Set_Cursor(60, 50 + 26 * i + ARRAY_OFFSET);
		GLCD_printf("No.", BLACK, WHITE, strCursor);
		myItoa(i + 1, index, 10);
		strCursor = Set_Cursor(84, 50 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(index, BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(92, 50 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(": ", BLACK, WHITE, strCursor);
		ftoa(str_time, Player_Time[i], 5);
		strCursor = Set_Cursor(108, 50 + 26 * i + ARRAY_OFFSET);
		GLCD_printf("Player ", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(164, 50 + 26 * i + ARRAY_OFFSET);
		str[0] = Player_Time_Order[i];
		str[1] = '\0';
		GLCD_printf(str, BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(188, 50 + 26 * i + ARRAY_OFFSET);
		
		GLCD_printf_window(str_time, BLACK, WHITE, strCursor, 7);
		strCursor = Set_Cursor(244, 50 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(" s", BLACK, WHITE, strCursor);
	}
	delayMs(500);
	
	while(1)
	{
		if(GetTS().pvalue == 1024)
			return 1;
	}
}

INT8U Menu_Multiple(INT8U Num)
{
	#define ARRAY_OFFSET 25
	
	INT8U i,n = 0;
	INT8U current_rand = 0, saved_rand = 0;
	Cursor strCursor;
	char str_time[10] = {0};
	char index[2] = {0};
	float least_time = 1.0e38;
	float Player_Time[5];
	char Player_Time_Order[10]={'1','2','3','4','5'};
	
	strCursor = Set_Cursor(0, 0);
	Lcd_ClearScr(320,240,0xffff);
  GLCD_printf(" Touch the screen when patterns change! ", 0xffff, RED, strCursor);
	
	if(Num == 0)
		return 0;
	for(i = 0; i != Num; ++i)
	{
		
	  delayMs(1000 + (rand() % 9000));
		srand(RTC_SEC);
		while((current_rand = rand() % 25) == saved_rand);
		saved_rand = current_rand;
		GLCD_RandomPattern(current_rand);
				
		Player_Time[i] = Time_Measure(PCLK_F);
		if(least_time >= Player_Time[i])
		{
			least_time = Player_Time[i];
			n=i+1;
		}
		ftoa(str_time, Player_Time[i], 5);
		strCursor = Set_Cursor(22, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf("Player ", BLACK, WHITE, strCursor);
		myItoa(i + 1, index, 10);
		strCursor = Set_Cursor(78, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(index, BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(86, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(": ", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(102, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf_window(str_time, BLACK, WHITE, strCursor, 7);
		strCursor = Set_Cursor(158, 30 + 26 * i + ARRAY_OFFSET);
		GLCD_printf(" s", BLACK, WHITE, strCursor);
		strCursor = Set_Cursor(68, 18);
		if(i!=Num - 1)
		{
			GLCD_printf("Touch to change player!", RED, WHITE, strCursor);
			delayMs(1000);
			while(GetTS().pvalue == 0);
			GLCD_printf("                       ", RED, WHITE, strCursor);
		}
	}
	
	ftoa(str_time, least_time, 5); // "Winner: Player 1 Time: 0.22222 s"
	
	strCursor = Set_Cursor(32, 200);
	GLCD_printf("Winner: ", RED, WHITE, strCursor);
	strCursor = Set_Cursor(96, 200);
	GLCD_printf("Player ", RED, WHITE, strCursor);
	myItoa(n, index, 10);
	strCursor = Set_Cursor(152, 200);
	GLCD_printf(index, RED, WHITE, strCursor);
	strCursor = Set_Cursor(160, 200);
	GLCD_printf(" Time: ", RED, WHITE, strCursor);
	strCursor = Set_Cursor(216, 200);
	GLCD_printf_window(str_time, RED, WHITE, strCursor, 7);
	strCursor = Set_Cursor(272, 200);
	GLCD_printf(" s", RED, WHITE, strCursor);
	
	delayMs(1000);

		while(1)
	{
		if(GetTS().pvalue == 1024)
		{
			Ranking(Player_Time,Player_Time_Order,Num);
			return 1;
		}
		
	}
  return 0;
}


void Menu_Calibrate(void)
{
	float T1TC_ABS, Time;
	char strPCLK[20];
	char strTime[20];
	Cursor strCursor1, strCursor2, buttonCursor1, buttonCursor2, buttonCursor3;
	touchscreen_data TSD;

	//while(GetTS().pvalue == 0);
  
	Lcd_ClearScr(320,240,WHITE);
	strCursor1 = Set_Cursor(24,112);
	GLCD_printf("Please wait for the calibration...",BLACK,WHITE,strCursor1);
	PCLK_F = Calibrate();
	Lcd_ClearScr(320,240,WHITE);
	//GLCD_Ellipsoid(200, 280, 130, 210, BLACK);
	
	myItoa(PCLK_F,strPCLK,10);
	strCursor1 = Set_Cursor(0,0);
	GLCD_printf("PCLK: ",BLACK,WHITE,strCursor1);
	strCursor1 = Set_Cursor(48,0);
	GLCD_printf(strPCLK,BLACK,WHITE,strCursor1);
	strCursor1 = Set_Cursor(120,0);
	GLCD_printf("Hz",BLACK,WHITE,strCursor1);
	
	strCursor1 = Set_Cursor(112,80);
	strCursor2 = Set_Cursor(192,80);
	buttonCursor1 = Set_Cursor(88,162);	// "Run"
	buttonCursor2 = Set_Cursor(80,162);	// "Pause"
	buttonCursor3 = Set_Cursor(204,162);	// Back button
	GLCD_Ellipsoid(60, 140, 130, 210, LIGHT_BLUE);	// Run button
	GLCD_Ellipsoid(180, 260, 130, 210, LIGHT_BLUE);	// Back button
	GLCD_printf("Back", WHITE, LIGHT_BLUE, buttonCursor3);
	
	ts_settling_delay();
	ts_settling_delay();
	ts_settling_delay();
	
	while(1)
	{
		TSD = GetTS_Fast();
		GLCD_printf("0.00000000 s", BLACK, WHITE, strCursor1);
		GLCD_printf("Run", WHITE, LIGHT_BLUE, buttonCursor1);
		if(TSD.pvalue != 0 && TSD.xvalue > 60 && TSD.xvalue < 140 && TSD.yvalue > 130 && TSD.yvalue < 210)
		{
			Init_Timer();
			Start_Timer();
			GLCD_Ellipsoid(60, 140, 130, 210, RED);
			GLCD_printf("Pause", WHITE, RED, buttonCursor2);
			
			
			while(1)
			{
				T1TC_ABS = T1TC;
				Time = T1TC_ABS/PCLK_F;
				ftoa(strTime, Time, 8);
				GLCD_printf(strTime, BLACK, WHITE, strCursor1);
				GLCD_printf(" s", BLACK, WHITE, strCursor2);
				TSD = GetTS_Fast();
				if(TSD.pvalue != 0 && TSD.xvalue > 180 && TSD.xvalue < 260 && TSD.yvalue > 130 && TSD.yvalue < 210)
					return;
				else if(TSD.pvalue != 0 && TSD.xvalue > 60 && TSD.xvalue < 140 && TSD.yvalue > 130 && TSD.yvalue < 210)
					break;
			}						
			GLCD_Ellipsoid(60, 140, 130, 210, BLACK);
			GLCD_printf("Reset", WHITE, BLACK, buttonCursor2);
			//ts_settling_delay();
			
			while(1)
			{
				TSD = GetTS_Fast();
				if(TSD.pvalue != 0 && TSD.xvalue > 180 && TSD.xvalue < 260 && TSD.yvalue > 130 && TSD.yvalue < 210)
					return;
				else if(TSD.pvalue != 0 && TSD.xvalue > 60 && TSD.xvalue < 140 && TSD.yvalue > 130 && TSD.yvalue < 210)
					break;
			}
			GLCD_Ellipsoid(60, 140, 130, 210, LIGHT_BLUE);	// Run button
			//ts_settling_delay();
		}
		else if(TSD.pvalue != 0 && TSD.xvalue > 180 && TSD.xvalue < 260 && TSD.yvalue > 130 && TSD.yvalue < 210)
		{
			break;
		}
	}
}
