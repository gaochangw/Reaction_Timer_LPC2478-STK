#include "data_types.h"
#include "lcd_text.h"
#ifndef LCD_DRAW_H
#define LCD_DRAW_H
#define BLACK  0x0000
#define WHITE  0xFFFF
#define BLUE   0x001f
#define GREEN  0x001f<<5
#define RED    0x001f<<10
#define LIGHT_BLUE  0x1F3F

typedef struct _Bmp_t {
  INT32U  H_Size;
  INT32U  V_Size;
  INT32U  BitsPP;
  INT32U  BytesPP;
  pINT32U pPalette;
  pINT32U pPicStream;
  pINT8U  pPicDesc;
} Bmp_t, *pBmp_t;

typedef struct _FontType_t {
  INT32U H_Size;
  INT32U V_Size;
  INT32U CharacterOffset;
  INT32U CharactersNuber;
  pINT8U pFontStream;
  pINT8U pFontDesc;
} FontType_t, *pFontType_t;


typedef INT32U LdcPixel_t, *pLdcPixel_t;
void PutPixel(INT32S x,INT32S y,INT16S c);
void putarea(INT32S x_start,INT32S x_end,INT32S y_start,INT32S y_end,INT16S c);
void Lcd_ClearScr(INT32S x,INT32S y,INT32S c);
void test_touch(INT32S x,INT32S y);
void fillmosaic(void);
void GLCD_Ellipsoid(INT16U x_start, INT16U x_end, INT16U y_start, INT16U y_end,INT16S c);
void PutPicture(const unsigned char* PicStream, const INT16U x_resolution, const INT16U y_resolution, Cursor picCursor);
void GLCD_Triangle(INT32S x1, INT32S y1, INT32S x2, INT32S y2, INT32S x3, INT32S y3, INT16S c);
void GLCD_RandomPattern(INT8U rand_number);
void GLCD_RoundRect(INT32S x_start, INT32S x_end, INT32S y_start, INT32S y_end, float r, INT32S c);
#endif
