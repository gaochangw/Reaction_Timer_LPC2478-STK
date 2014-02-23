#include "data_types.h"
#ifndef MENU_H
#define MENU_H

INT8U Start_Animation(void);
INT8U Menu_Main(void);
INT8U Game(void);
INT8U Menu_Player(void);
INT8U Ranking(float* Player_Time,char* Player_Time_Order,INT8U k);
INT8U Menu_Multiple(INT8U Num);
INT8U Menu_Single(void);
void Time_Display(INT16S FT_Color, INT16S BG_Color);
void Menu_Calibrate(void);
INT8U Menu_GameMode(void);
#endif
