#include "lpc2478.h"
#include "lcd_draw.h"
#include "lcd_text.h"
#include "low_level_init.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define C_GLCD_H_SIZE           320
#define C_GLCD_V_SIZE           240
#define TEXT_DEF_TAB_SIZE 3

class LCD_Vector
{
	public:
		INT32S x;
		INT32S y;
		LCD_Vector():x(0),y(0){}										// Default constructor
		LCD_Vector(INT32S x_value, INT32S y_value)	// Assignment constructor
		{
			x = x_value;
			y = y_value;
		}
		~LCD_Vector(){}	// Destructor
			
		LCD_Vector assign(const INT32S x_value, const INT32S y_value)	// Assignment
		{
			x = x_value;
			y = y_value;
			return *this;
		}
	
		LCD_Vector operator =(const LCD_Vector& p)	// Assignment
		{
			x = p.x;
			y = p.y;
			return *this;
		}
		
		LCD_Vector operator +(const LCD_Vector& p)	// Vector addition
		{
			return LCD_Vector(x + p.x, y + p.y);
		}
		
		LCD_Vector operator -(const LCD_Vector& p)	// Vector subtraction
		{
			return LCD_Vector(x - p.x, y - p.y);
		}
		
		INT32S operator *(const LCD_Vector& p)	// Dot product
		{
			return (x * p.x + y * p.y);
		}
		
		double abs(void)
		{
			return (sqrt(double(x*x + y*y)));
		}
		
		INT32S cross(const LCD_Vector& p)
		{
			return (x*p.y - y*p.x);
		}
};






/*-----------------------------------------------------------------------------
 *  320 x 240 TFT LCD单个象素的显示数据输出
 */
void PutPixel(INT32S x,INT32S y,INT16S c)
{
    if(x < 320 && y < 240)
      *(volatile INT16U *)(SDRAM_BASE + 2*(x + 320 * y)) = c;
}

/*void PutPicture(const unsigned char* PicStream)
{
	INT16U x = 0;
	INT16U y = 0;
	
	for(y = 75; y != 165 ; ++y)
	{
		for(x = 230; x != 410; ++x)
		{
			*(volatile INT16U *)(SDRAM_BASE + (x + 640 * y)) = (PicStream[(x - 230) + 180 * (y - 75)]);
		}
	}
}*/

void PutPicture(const unsigned char* PicStream, const INT16U x_resolution, const INT16U y_resolution, Cursor picCursor)
{
	INT16U x = 0;
	INT16U y = 0;
	INT16S color = 0;
	INT16U x_start, x_end, y_start, y_end;
	
	x_start = picCursor.xValue - x_resolution/2;
	x_end   = picCursor.xValue + x_resolution/2;
	y_start = picCursor.yValue - y_resolution/2;
	y_end   = picCursor.yValue + y_resolution/2;
	
	for(y = y_start; y != y_end ; ++y)
	{
		for(x = x_start; x != x_end; ++x)
		{
			color = PicStream[2*((x - x_start) + x_resolution * (y - y_start))] + 
			                 (PicStream[2*((x - x_start) + x_resolution * (y - y_start)) + 1] << 8 );
			PutPixel(x, y, color);
		}
	}
}

/***************************************************************
ellipsoid
*************************************************************/
void GLCD_Ellipsoid(INT16U x_start, INT16U x_end, INT16U y_start, INT16U y_end, INT16S c)
{
	float a = (x_end-x_start)/2;
	float b = (y_end-y_start)/2;
	float x = 0, y = 0;
	if(x_start<x_end && x_end<320 && y_start<y_end && y_end<240)
	{
	  for(x=x_start;x<=x_end;x++)
		{
	  	for(y=y_start;y<=y_end;y++)
				if((x-a-x_start)*(x-a-x_start)/(a*a)+(y-b-y_start)*(y-b-y_start)/(b*b)<1)
				{
					PutPixel((int)x,(int)y,c);
				}			
	  }
	}
}

void GLCD_Triangle(INT32S x1, INT32S y1, INT32S x2, INT32S y2, INT32S x3, INT32S y3, INT16S c)
{
	INT32S x_min = x1;
	INT32S x_max = x1; 
	INT32S y_min = y1; 
	INT32S y_max = y1;
	INT32S x = 0,y = 0;
	
	LCD_Vector PA(0,0);
	LCD_Vector PB(0,0);
	LCD_Vector PC(0,0);
	INT32S PA_PB = 0;
	INT32S PB_PC = 0;
	INT32S PC_PA = 0;
	
	x_min = (x_min > x2)? x2 : x_min;
	x_min = (x_min > x3)? x3 : x_min;
	x_max = (x_max < x2)? x2 : x_max;
	x_max = (x_max < x3)? x3 : x_max;
	
	y_min = (y_min > y2)? y2 : y_min;
	y_min = (y_min > y3)? y3 : y_min;
	y_max = (y_max < y2)? y2 : y_min;
	y_max = (y_max < y3)? y3 : y_min;
	
	

	for(x = x_min; x != x_max; ++x)
	{
		for(y = y_min; y != y_max; ++y)
		{
			PA.assign(x1 - x, y1 - y);
			PB.assign(x2 - x, y2 - y);
			PC.assign(x3 - x, y3 - y);
			PA_PB = PA.cross(PB);
			PB_PC = PB.cross(PC);
			PC_PA = PC.cross(PA);
			if((PA_PB>0 && PB_PC>0 && PC_PA>0) /*|| (PA_PB<0 && PB_PC<0 && PC_PA<0)*/)
				PutPixel(x, y, c);
		}
	}			
}

/**************************************************************
填充某一特定区块为特定颜色
**************************************************************/
void putarea(INT32S x_start,INT32S x_end,INT32S y_start,INT32S y_end,INT16S c)
{
	INT32S x,y;
	if(x_start<x_end && x_end<320 && y_start<y_end && y_end<240)
	{
	 for(x=x_start;x<=x_end;x++)
	 	{
		for(y=y_start;y<=y_end;y++)
			PutPixel(x,y,c);
		}
	}
}

/**************************************************************
填充马赛克
**************************************************************/
void fillmosaic(void)
	{
	INT16S color[]={0x07e0,0xf800,0x001f,0xff00,0xffff,0x0000,0x02fe};
	INT32S i,j,k=0;
	for(i=0;i<=4;i++)
		{for(j=0;j<=4;j++)
			{
			 putarea(64*j,(64*(j+1)-1),48*i,(48*(i+1)-1),color[k]);
			 if(k++==6)
			 k=0;
			 }
		}	
	}
/**************************************************************
800×480 16Bpp TFT LCD全屏填充特定颜色单元或清屏
**************************************************************/

void Lcd_ClearScr(INT32S x,INT32S y,INT32S c)
{

        INT32S i = 0;
        while (i < x * y)
        {
            *(volatile INT16U *)(SDRAM_BASE + i * 2) = c;
            i += 1;
        }
}

void GLCD_RandomPattern(INT8U rand_number)
{
		switch(rand_number)
		{
			case 0:
				putarea(200, 300, 70, 170, BLUE);	// Square
				break;
			case 1:
				putarea(200, 300, 70, 170, RED);
				break;
			case 2:
				putarea(200, 300, 70, 170, GREEN);
				break;
			case 3:
				putarea(200, 300, 70, 170, BLACK);
				break;
			case 4:
				putarea(200, 300, 70, 170, LIGHT_BLUE);
				break;
			case 5:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Triangle(200, 170, 250, 70, 300, 170, BLUE);	// Triangle
				break;
			case 6:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Triangle(220, 170, 230, 70, 300, 150, RED);
				break;
			case 7:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Triangle(240, 170, 210, 70, 300, 130, GREEN);
				break;
			case 8:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Triangle(260, 170, 200, 80, 300, 110, BLACK);
				break;
			case 9:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Triangle(280, 170, 200, 100, 300, 90, LIGHT_BLUE);
			  break;
			case 10:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 100 ,140, RED);	// Circle
				break;
			case 11:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 100 ,140, BLUE);
				break;
			case 12:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 100 ,140, GREEN);
				break;
			case 13:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 100 ,140, BLACK);
				break;
			case 14:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 100 ,140, LIGHT_BLUE);
				break;
			case 15:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(200, 300, 100 ,140, RED);	// Horizontal ellipsoid
				break;
			case 16:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(200, 300, 100 ,140, GREEN);
				break;
			case 17:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(200, 300, 100 ,140, BLUE);
				break;
			case 18:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(200, 300, 100 ,140, BLACK);
				break;
			case 19:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(200, 300, 100 ,140, LIGHT_BLUE);
				break;
			case 20:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 70 ,170, RED);	// Vertical ellipsoid
				break;
			case 21:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 70 ,170, GREEN);	
				break;
			case 22:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 70 ,170, BLUE);	
				break;
			case 23:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 70 ,170, BLACK);	
				break;
			case 24:
				putarea(200, 300, 70, 170, WHITE);
				GLCD_Ellipsoid(230, 270, 70 ,170, LIGHT_BLUE);	
				break;
			default:
				break;
		}
}

void GLCD_RoundRect(INT32S x_start, INT32S x_end, INT32S y_start, INT32S y_end, float r, INT32S c)
{
	float x = 0, y = 0;
	
		putarea(x_start,x_end,y_start+r,y_end-r,c);
		putarea(x_start+r,x_end-r,y_start,y_start+r,c);
		putarea(x_start+r,x_end-r,y_end-r,y_end,c);
		
		// Top left
		for(x=x_start;x<=x_start+r;x++)
		{
	  	for(y=y_start;y<=y_start+r;y++)
				if((x-x_start-r)*(x-x_start-r)+(y-y_start-r)*(y-y_start-r)<r*r)
				{
					PutPixel((int)x,(int)y,c);
				}			
		}
		
		// Top right
		for(x=x_end-r;x<=x_end;x++)
		{
	  	for(y=y_start;y<=y_start+r;y++)
				if((x-x_end+r)*(x-x_end+r)+(y-y_start-r)*(y-y_start-r)<r*r)
				{
					PutPixel((int)x,(int)y,c);
				}			
		}
		
		// Bottom right
		for(x=x_end-r;x<=x_end;x++)
		{
	  	for(y=y_end-r;y<=y_end;y++)
				if((x-x_end+r)*(x-x_end+r)+(y-y_end+r)*(y-y_end+r)<r*r)
				{
					PutPixel((int)x,(int)y,c);
				}
		}
		
		// Bottom left
		for(x=x_start;x<=x_start+r;x++)
		{
	  	for(y=y_end-r;y<=y_end;y++)
				if((x-x_start-r)*(x-x_start-r)+(y-y_end+r)*(y-y_end+r)<r*r)
				{
					PutPixel((int)x,(int)y,c);
				}
		}
}


/**************************************************************
// LCD display is flipped vertically
// But, think the algorithm by mathematics point.
//   3I2
//   4 I 1
//  --+--   <-8 octants  mathematical cordinate
//   5 I 8
//   6I7
**************************************************************/
void Glib_Line(INT32S x1,INT32S y1,INT32S x2,INT32S y2,INT32S color)
{
	INT32S dx,dy,e;
	dx=x2-x1;
	dy=y2-y1;

	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

/**************************************************************
在LCD屏幕上画一个矩形
**************************************************************/
void Glib_Rectangle(INT32S x1,INT32S y1,INT32S x2,INT32S y2,INT32S color)
{
    Glib_Line(x1,y1,x2,y1,color);
    Glib_Line(x2,y1,x2,y2,color);
    Glib_Line(x1,y2,x2,y2,color);
    Glib_Line(x1,y1,x1,y2,color);
}

/**************************************************************
在LCD屏幕上用颜色填充一个矩形
**************************************************************/
void Glib_FilledRectangle(INT32S x1,INT32S y1,INT32S x2,INT32S y2,INT32S color)
{
    INT32S i;

    for(i=y1;i<=y2;i++)
	Glib_Line(x1,i,x2,i,color);
}


