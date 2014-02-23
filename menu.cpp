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


static INT32U PCLK_F = 28756299;


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
		case 0 : strcpy(strWday,"Mon"); break;
		case 1 : strcpy(strWday,"Tue"); break;
		case 2 : strcpy(strWday,"Wed"); break;
		case 3 : strcpy(strWday,"Thu"); break;
		case 4 : strcpy(strWday,"Fri"); break;
		case 5 : strcpy(strWday,"Sat"); break;
		case 6 : strcpy(strWday,"Sun"); break;
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

/***************************
main menu
***************************/
INT8U Menu_Main(void)
{
	Cursor strCursor;
	touchscreen_data TouchData;
	
	/* Draw patterns */
	Lcd_ClearScr(320,240,0xffff);
	putarea(0, 319, 0, 16, BLACK);
	strCursor = Set_Cursor(40,138);
	GLCD_Ellipsoid(20, 100, 105, 185, 0x0000);
	GLCD_printf("START", 0xffff, 0x0000, strCursor);
	strCursor = Set_Cursor(142,140);
	GLCD_printf("Super Reaction Timer", 0x0000, 0xffff, strCursor);
	strCursor = Set_Cursor(7,220);
	GLCD_printf("Authors: C.Gao, Z.Y.Fu, H.Zhang, T.Zhu", 0x0000, 0xffff, strCursor);
	Logo();
	
	/* Detect touch */
	while(1)
	{
		Time_Display(WHITE, BLACK);
		TouchData = GetTS();
		if(TouchData.pvalue != 0 && TouchData.xvalue > 20 && TouchData.xvalue < 100 && TouchData.yvalue > 105 && TouchData.yvalue < 185)
			return 1;
	}
}

/*****************************
player menu
******************************/

INT8U Menu_Player(void)
{
	Cursor strCursor;
	touchscreen_data TouchData;

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
		TouchData = GetTS();
		if(TouchData.pvalue != 0 && TouchData.xvalue > 135 && TouchData.xvalue < 185 && TouchData.yvalue > 95 && TouchData.yvalue < 145)
			return 0;
		if(TouchData.pvalue != 0 && TouchData.xvalue > 40 && TouchData.xvalue < 140 && TouchData.yvalue > 40 && TouchData.yvalue < 100)
			return 2;
		if(TouchData.pvalue != 0 && TouchData.xvalue > 40 && TouchData.xvalue < 140 && TouchData.yvalue > 140 && TouchData.yvalue < 200)
			return 4;
		if(TouchData.pvalue != 0 && TouchData.xvalue > 180 && TouchData.xvalue < 280 && TouchData.yvalue > 40 && TouchData.yvalue < 100)
			return 3;
		if(TouchData.pvalue != 0 && TouchData.xvalue > 180 && TouchData.xvalue < 280 && TouchData.yvalue > 140 && TouchData.yvalue < 200)
			return 5;
	}
}


BOOL Menu_GameMode(void)
{
	Cursor strCursor;
	touchscreen_data TouchData;
	
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
			TouchData = GetTS();
			if(TouchData.pvalue != 0 && TouchData.xvalue > 145 && TouchData.xvalue < 175 && TouchData.yvalue > 115 && TouchData.yvalue < 145)     /*Back*/     
			{
				return 0;
			}
			else if(TouchData.pvalue != 0 && TouchData.xvalue > 40 && TouchData.xvalue < 140 && TouchData.yvalue > 50 && TouchData.yvalue < 110)    /*Single player*/
			{
				Menu_Single();
				break;
			}
			else if(TouchData.pvalue != 0 && TouchData.xvalue > 180 && TouchData.xvalue < 280 && TouchData.yvalue > 50 && TouchData.yvalue < 110)  /*Multiple Players*/
			{
				Menu_Multiple(Menu_Player());
				break;
			}
			else if(TouchData.pvalue != 0 && TouchData.xvalue > 40 && TouchData.xvalue < 140 && TouchData.yvalue > 150 && TouchData.yvalue < 210)  /*Menu_Calibrate*/
			{
				Menu_Calibrate();
				break;
			}
			else if(TouchData.pvalue != 0 && TouchData.xvalue > 180 && TouchData.xvalue < 280 && TouchData.yvalue > 150 && TouchData.yvalue < 210)  /*Menu_Calibrate*/
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
		
		GLCD_printf("0.00000000 s", BLACK, WHITE, strCursor1);
		GLCD_printf("Run", WHITE, LIGHT_BLUE, buttonCursor1);
		if(GetTS().pvalue != 0 && GetTS().xvalue > 60 && GetTS().xvalue < 140 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
		{
			Init_Timer();
			Start_Timer();
			GLCD_Ellipsoid(60, 140, 130, 210, RED);
			GLCD_printf("Pause", WHITE, RED, buttonCursor2);
			ts_settling_delay();
			
			while(1)
			{
				T1TC_ABS = T1TC;
				Time = T1TC_ABS/PCLK_F;
				ftoa(strTime, Time, 8);
				GLCD_printf_window(strTime, BLACK, WHITE, strCursor1, 10);
				GLCD_printf(" s", BLACK, WHITE, strCursor2);
				if(GetTS().pvalue != 0 && GetTS().xvalue > 180 && GetTS().xvalue < 260 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
					return;
				else if(GetTS().pvalue != 0 && GetTS().xvalue > 60 && GetTS().xvalue < 140 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
					break;
			}						
			GLCD_Ellipsoid(60, 140, 130, 210, BLACK);
			GLCD_printf("Reset", WHITE, BLACK, buttonCursor2);
			ts_settling_delay();
			
			while(1)
			{
				if(GetTS().pvalue != 0 && GetTS().xvalue > 180 && GetTS().xvalue < 260 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
					return;
				else if(GetTS().pvalue != 0 && GetTS().xvalue > 60 && GetTS().xvalue < 140 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
					break;
			}
			GLCD_Ellipsoid(60, 140, 130, 210, LIGHT_BLUE);	// Run button
			ts_settling_delay();
		}
		else if(GetTS().pvalue != 0 && GetTS().xvalue > 180 && GetTS().xvalue < 260 && GetTS().yvalue > 130 && GetTS().yvalue < 210)
		{
			break;
		}
	}
}
