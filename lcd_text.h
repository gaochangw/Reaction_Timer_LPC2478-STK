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
#include "data_types.h"

#ifndef LCD_TEXT_H
#define LCD_TEXT_H

/* Cursor */
typedef struct Cursor_t
{
	INT16U xValue;
	INT16U yValue;
}Cursor;

Cursor Set_Cursor(INT16U x, INT16U y);	// Set up the string cursor
void GLCD_putchar(INT8U c, INT16S FT_Color, INT16S BG_Color, Cursor xy);
void GLCD_printf(char* ptr, INT16S FT_Color, INT16S BG_Color, Cursor xy);	// Print a string on LCD
void GLCD_printf_window(char* ptr, INT16S FT_color, INT16S BG_color, Cursor xy, INT16U length);
char* myItoa(INT32U i, char *a, INT8U radix);
int ftoa(char *str, float num, int n);
#endif
