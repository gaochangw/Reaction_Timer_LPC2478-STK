/***********************************************************************
 * File:   lcd_driver.h
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains driver support for LCD panel used on FCC1 Board
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "LPC24xx.h"

#include "clcdc.h"

/* LCD palette register type */
typedef struct
{
    INT32U Rl:5;
    INT32U Gl:5;
    INT32U Bl:5;
    INT32U Il:1;
    INT32U Ru:5;
    INT32U Gu:5;
    INT32U Bu:5;
    INT32U Iu:1;
} PALETTE_ENTRY_T;

/* LCD bits per pixel types */
typedef enum {
    BPP_IS_1 = 1,
    BPP_IS_2,
    BPP_IS_4,
    BPP_IS_8,
    BPP_IS_16,
    BPP_IS_24,
    BPP_IS_16_565_MODE,
    BPP_IS_12_444_MODE
} LCD_BPP_T;

/***********************************************************************
 * LCD device configuration commands (IOCTL commands and arguments)
 **********************************************************************/

/* LCD device commands (IOCTL commands) */
typedef enum {
    LCD_SET_BUFFER,     /* Set LCD display frame buffer, 
                           arg = memory pointer for image to be displayed */
    LCD_CRSR_SET_BUFFER,/* Set LCD display frame buffer, 
                           arg = memory pointer for image to be displayed */
    LCD_PWR_ON,         /* Turn on the LCD controller power, arg = 1, turn on, 
                           arg = 0, turn off */
    LCD_ENABLE,         /* Enable the LCD controller, arg = 1, enable, 
                           arg = 0, disable */
    LCD_CRSR_ENABLE,    /* Enable the LCD cursor, arg = 1, enable, 
                           arg = 0, disable */
    LCD_CRSR_NUM,       /* Select the LCD cursor number, arg = 0, 64x64, 
                           arg = 0, 1, 2, 3, 32x32 */
    LCD_CRSR_SIZE,      /* Set the LCD cursor size, arg = 1, 64x64, 
                           arg = 0, 32x32 */
    LCD_CRSR_SYNC,      /* Set the LCD cursor frame sync, arg = 1, sync, 
                           arg = 0, async */
    LCD_LOAD_PALETTE,   /* This function supports loading of the color 
                           palette from the C file generated by the bmp2c utility. 
                           It expects the palette to be passed as an array of 32-bit 
                           BGR entries having the following format:
                           7:3 - Blue
                           2:0 - Not used
                           15:11 - Green
                           10:8 - Not used
                           23:19 - Red
                           18:16 - Not used
                           31:24 - Not used
                           arg = pointer to input palette table address*/
    LCD_CRSR_LOAD_PALETTE0,   /* 7:0 - Red
                                 15:8 - Green
                                 23:16 - Blue
                                 31:24 - Not used*/
    LCD_CRSR_LOAD_PALETTE1,   /* 7:0 - Red
                                 15:8 - Green
                                 23:16 - Blue
                                 31:24 - Not used*/
    LCD_SET_BPP,        /* Set current display bits per pixel, 
                           arg = bits per pixel */
    LCD_SET_BGR,        /* LCD invert the bgr bit in the LCD controller. 
                           arg = 1, invert BGR for reverse color, arg = 0, BGR for normal color */
    LCD_SET_INTERRUPT,  /* Set interrupt mask set/clear register */
    LCD_CLR_INTERRUPT,  /* Set interrupt clear register*/
    LCD_CRSR_SET_INTERRUPT,  /* Set cursor interrupt mask set/clear register */
    LCD_CRSR_CLR_INTERRUPT,  /* Set cursor interrupt clear register*/
    LCD_CRSR_XY,        /* Set LCD cursor xy position register */
    LCD_CRSR_CLIP,      /* Set LCD cursor clip position register */
    LCD_GET_STATUS      /* Get a lcd status, use an argument type of
                           LCD_IOCTL_STS_T as the argument to return the correct status */
} LCD_IOCTL_CMD_T;

/* LCD device arguments for LCD_GET_STATUS command (IOCTL arguments) */
typedef enum {
    LCD_GET_BUFFER,     /* Returns LCD fram buffer address */
    LCD_GET_BPP,        /* Returns current LCD panel bit per pixel */
    LCD_GET_PALETTE,    /* Returns a pointer to palette table */
    LCD_CRSR_GET_PALETTE0,    /* Returns a pointer to cursor palette table */
    LCD_CRSR_GET_PALETTE1,    /* Returns a pointer to cursor palette table */
    LCD_GET_INTERRUPT,  /* Get interrupt mask sstatus register */
    LCD_CRSR_GET_INTERRUPT   /* Get cursor interrupt mask sstatus register */
} LCD_IOCTL_STS_T;

/***********************************************************************
 * LCD driver functions
 **********************************************************************/
/* Open the lcd */
INT32S lcd_open(void *lcdbase, INT32S arg);

/* Close the lcd */
INT32S lcd_close(INT32S devid);

/* lcd configuration block */
INT32S lcd_ioctl(INT32S devid, INT32S cmd, INT32S arg);
void gpio0_handler(void);
#endif /* LCD_DRIVER_H */
