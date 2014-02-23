/*
 *    (c) Copyright Chang Gao, Ziyou Fu, Hui Zhang, Tao Zhu
 *
 *				             University of Liverpool
 *				Department of Electrical Engineering and Electronics
 *
 *    File name   : Font_8_16.h
 *    Description : 8*16 dot matrix for Times New Roman font
 *    Date        : 1, Feb 2014
 *    Author      : Chang Gao & Ziyou Fu
 *    Environment : Keil Uvision v4
 *    Emulator    : Keil Ulink 2
 *    Board       : Olimex LPC2478-STK
 *    Touch Sreen : 320*240 TFT LCD
 *
 **************************************************************************/
#include "lcd_text.h"
#include "lcd_draw.h"
#include "Font_8_16.h"
/* Set string cursor */
Cursor Set_Cursor(INT16U x, INT16U y)
{
	Cursor strCursor;
	strCursor.xValue = x;
	strCursor.yValue = y;
	return strCursor;
}

/* Putchar */
void GLCD_putchar(INT8U c, INT16S FT_Color, INT16S BG_Color, Cursor xy)
{
	int k = 0,i = 0, j = 0;
	INT8U Temp_Stream = 0;
	INT16U Pixel_Stream[16][8];
	k = c - CH_OFFSET;
	for (i = 0; i != 16; ++i)
	{
		Temp_Stream = CH_Stream_8_16[k][i];
		for (j = 0; j != 8; ++j)
		{
			if ((Temp_Stream & 0x80) == 0x80)
				Pixel_Stream[i][j] = FT_Color;	// Font color
			else
				Pixel_Stream[i][j] = BG_Color;	// Background color*/
			Temp_Stream = Temp_Stream << 1;
		}
	}		
	for (i = 0; i != 16; ++i)
	{
		for (j = 0; j != 8; ++j)
			PutPixel(j + xy.xValue, i + xy.yValue, Pixel_Stream[i][j]);
	}
}

void GLCD_printf(char* ptr, INT16S FT_Color, INT16S BG_Color, Cursor xy)
{
	int a=0;
	Cursor xy_temp;
	xy_temp.xValue = xy.xValue;
	xy_temp.yValue = xy.yValue;
	while(*ptr)
  {
		a=(int)*ptr;
		switch(a)
		{
			case 10:	// Line feed
				xy_temp = Set_Cursor(xy.xValue, xy.yValue + 16);
				break;
			default:
				GLCD_putchar(a, FT_Color, BG_Color, xy_temp);
				xy_temp.xValue += 8;
				break;
		}
		ptr++;
  }
}

void GLCD_printf_window(char* ptr, INT16S FT_color, INT16S BG_color, Cursor xy, INT16U length)
{
	int a=0;
	Cursor xy_temp;
	xy_temp.xValue = xy.xValue;
	xy_temp.yValue = xy.yValue;
	putarea(xy.xValue, xy.xValue + 8*length - 1, xy.yValue, xy.yValue + 15, BG_color);
	while(*ptr)
  {
		a=(int)*ptr;
		switch(a)
		{
			case 10:	// Line feed
				xy_temp = Set_Cursor(xy.xValue, xy.yValue + 16);
				break;
			default:
				GLCD_putchar(a,FT_color, BG_color, xy_temp);
				xy_temp.xValue += 8;
				break;
		}
		ptr++;
  }
}

char* myItoa(INT32U i, char *a, INT8U radix) 
{ 
        INT8S n, m=0; 
        INT8U temp[10]; 
        for(n=9; n>=0; n--) 
        { 
                temp[n] = i%radix + '0'; 
                i /= radix; 
        } 
        for(n=0; n<9; n++) 
        { 
                if(temp[n]!='0') 
                        break; 
        } 
        for(; n<10; n++) 
        { 
                a[m++] = temp[n];  
        } 
        a[m++] = 0; 
        return(a); 
} 

/* Cited from: http://blog.csdn.net/hui_love2046/article/details/5760907 */
int ftoa(char *str, float num, int n)
{
    int     sumI;
    float   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;

    char *p;
    char *pp;

    if(str == NULL) return -1;
    p = str;

    /*Is less than 0*/
    if(num < 0)
    {
        sign = 1;
        num = 0 - num;
    }

    sumI = (int)num;    //sumI is the part of int
    sumF = num - sumI;  //sumF is the part of float

    /*Int ===> String*/
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);

    /*******End*******/

    if(sign == 1)
    {
        *(str++) = '-';
    }
    pp = str;
    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }
    *(str++) = '.';     //point

    /*Float ===> String*/
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';
        if((++count) == n)
            break;
        sumF = sumF*10 - temp;
    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return 0;
}
