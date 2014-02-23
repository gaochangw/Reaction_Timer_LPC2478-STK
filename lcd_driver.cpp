/***********************************************************************
 * File:   lcd_driver.c
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains driver support for the LCD panel on FCC1 Board
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#include "lcd_params.h"
#include "lcd_driver.h"
#include "target.h"

/***********************************************************************
 * LCD driver private data and types
 **********************************************************************/

/* LCD device configuration structure type */
typedef struct
{
    BOOL1 init;          /* Device initialized flag */
    CLCDC_REGS_T *regptr;  /* Pointer to LCD registers */
    LCD_PARAM_T *dptr;     /* Pointer to LCD controller settings */
} CLCDC_CFG_T;

/***********************************************************************
 * Forward declration
 **********************************************************************/
void lcd_configure_gpio(void);
void lcd_source_driver_digital_voltage_on(void);
void lcd_source_driver_analog_voltage_on(void);
void lcd_gate_driver_low_voltage_on(void);
void lcd_gate_driver_high_voltage_on(void);
void lcd_backlight_on(void);
void lcd_backlight_off(void);
void lcd_gate_driver_high_voltage_off(void);
void lcd_gate_driver_low_voltage_off(void);
void lcd_source_driver_analog_voltage_off(void);
void lcd_source_driver_digital_voltage_off(void);

/* LCD device configuration structure */
static CLCDC_CFG_T lcdcfg;

/***********************************************************************
 *
 * Function: lcd_configure_gpio
 *
 * Purpose: Configure the GPIO muxing for LCD based on LCD type
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_configure_gpio(void)
{
   
   PINSEL2|=0x00000C00;	                //p1.5->pwm0.3
//   PINSEL0|=0x00055500;
   PINSEL3|=0x05555500;
   PINSEL4|=0x054fffff;
   PINSEL9|=0x0a000000;

   CLCDPINSEL = 0x0000000d;    /* TFT 16bpp (1:5:5:5)bgr */
//   CLCDPINSEL = 0x0000000b;    /* TFT 16bpp (5:6:5)bgr */


}

/*********************************************************************************************************
** 函数名称:  PWM2_InitDft
** 功能描述:  PWM2初始化并启动输出, 设置P3.25为PWM1.2输出,匹配时复位计数器,不使用PWM中断. 占空比设置为50％的单边沿PWM.
** 入口参数:  无
** 出口参数:  无
***********************************************************************************************************/
void PWM2_InitDft(void)
{
	PWM0TCR = 0x02;			// PWM1的计数器复位 
	PWM0PR 	= 0x00;			// 不分频,PWM1计数器的计数频率即Fpclk
	PWM0MCR = 0x02;			// 计数器里的值和匹配寄存器里的匹配值相等时复位
	PWM0PCR = 0x0000;		// 设置PWM2输出为单边沿PWM
    PWM0MR0 = Fpclk / 500;
    PWM0MR3 = PWM0MR0/ 1;	// 设置PWM3输出为50%占空比
	PWM0LER = 0x09;			// PWM0和PWM3匹配锁存
	PWM0PCR = 0x0800; 		// PWM3输出使能
   	PWM0TCR = 0x09;			// PWM和计数器都使能	
   	
} 

/***********************************************************************
 *
 * Function: lcd_source_driver_digital_voltage_on
 *
 * Purpose: Turn on lcd source driver digital voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_source_driver_digital_voltage_on(void)
{
//    IO1SET_bit.P1_19 = 1;
//    IO1CLR_bit.P1_19 = 1;
    IOCLR1 = 0x00080000;
}

/***********************************************************************
 *
 * Function: lcd_source_driver_analog_voltage_on
 *
 * Purpose: Turn on lcd source driver analog voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_source_driver_analog_voltage_on(void)
{
//    IO1SET_bit.P1_18 = 1;
//    IO1CLR_bit.P1_18 = 1;
    IOCLR1 = 0x00040000;
}

/***********************************************************************
 *
 * Function: lcd_gate_driver_low_voltage_on
 *
 * Purpose: Turn on lcd gate driver low voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_gate_driver_low_voltage_on(void)
{
//    IO0SET_bit.P0_30 = 1;
//    IO0CLR_bit.P0_30 = 1;
    IOCLR0 = 0x40000000;
}

/***********************************************************************
 *
 * Function: lcd_gate_driver_high_voltage_on
 *
 * Purpose: Turn on lcd gate driver high voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_gate_driver_high_voltage_on(void)
{
//    IO0SET_bit.P0_29 = 1;
//    IO0CLR_bit.P0_29 = 1;
    IOCLR0 = 0x20000000;
}

/***********************************************************************
 *
 * Function: lcd_backlight_on
 *
 * Purpose: Turn on lcd backlight
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_backlight_on(void)
{
//    IO0SET_bit.P0_18 = 1;
//    IO0CLR_bit.P0_18 = 1;
    IOCLR0= 0x00040000;
}

/***********************************************************************
 *
 * Function: lcd_backlight_off
 *
 * Purpose: Turn off lcd backlight
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_backlight_off(void)
{
//    IO0CLR_bit.P0_18 = 1;
//    IO0SET_bit.P0_18 = 1;
    IOSET0 = 0x00040000;
}

/***********************************************************************
 *
 * Function: lcd_gate_driver_high_voltage_off
 *
 * Purpose: Turn off lcd gate driver high voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_gate_driver_high_voltage_off(void)
{
//    IO0CLR_bit.P0_29 = 1;
//    IO0SET_bit.P0_29 = 1;
    IOSET0 = 0x20000000;
}

/***********************************************************************
 *
 * Function: lcd_gate_driver_low_voltage_off
 *
 * Purpose: Turn off lcd gate driver low voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_gate_driver_low_voltage_off(void)
{
//    IO0CLR_bit.P0_30 = 1;
//    IO0SET_bit.P0_30 = 1;
    IOSET0 = 0x40000000;
}

/***********************************************************************
 *
 * Function: lcd_source_driver_analog_voltage_off
 *
 * Purpose: Turn off lcd source driver analog voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_source_driver_analog_voltage_off(void)
{
//    IO1CLR_bit.P1_18 = 1;
//    IO1SET_bit.P1_18 = 1;
    IOSET1 = 0x00040000;
}

/***********************************************************************
 *
 * Function: lcd_source_driver_digital_voltage_off
 *
 * Purpose: Turn off lcd source driver digital voltage
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void lcd_source_driver_digital_voltage_off(void)
{
//    IO1CLR_bit.P1_19 = 1;
//    IO1SET_bit.P1_19 = 1;
    IOSET1 = 0x00080000;
}

/***********************************************************************
 *
 * Function: lcd_initialize
 *
 * Purpose: Initialize the LCD controller
 *
 * Processing:
 *     Prior to resetting LCD values, disable the LCD controller.
 *     Configurate the LCD registers with the values in the passed 
 *     LCD_PARAM_T structure.
 *
 * Parameters:
 *     lcdcfgptr : A pointer to an LCD configuration data structure
 *
 * Outputs: None
 *
 * Returns: _NO_ERROR if the LCD was initialized, otherwise _ERROR
 *
 **********************************************************************/
BOOL1 lcd_initialize(CLCDC_CFG_T *lcdcfgptr)
{
    INT32U tmp, i;
    INT32S status = _NO_ERROR;
    CLCDC_REGS_T *lcdptr = lcdcfgptr->regptr;
    LCD_PARAM_T *cgdatptr = lcdcfgptr->dptr;

    /* Disable the display in case it is on */
    lcdptr->lcdctrl &= ~CLCDC_LCDCTRL_ENABLE;

    /* Generate the horizontal axis plane control word */
    tmp = (CLCDC_LCDTIMING0_PPL(cgdatptr->pixels_per_line) |
        CLCDC_LCDTIMING0_HSW(cgdatptr->h_sync_pulse_width) |
        CLCDC_LCDTIMING0_HFP(cgdatptr->h_front_porch) |
        CLCDC_LCDTIMING0_HBP(cgdatptr->h_back_porch));
    lcdptr->lcdtiming0 = tmp;

    /* Generate the vertical axis plane control word */
    tmp = (CLCDC_LCDTIMING1_LPP(cgdatptr->lines_per_panel) |
        CLCDC_LCDTIMING1_VSW(cgdatptr->v_sync_pulse_width) |
        CLCDC_LCDTIMING1_VFP(cgdatptr->v_front_porch) |
        CLCDC_LCDTIMING1_VBP(cgdatptr->v_back_porch));
    lcdptr->lcdtiming1 = tmp;

    /* Generate the clock and signal polarity control word */
    if(cgdatptr->ac_bias_frequency != 0)
    {
	/* STN panel has AC bias value */
    	tmp = CLCDC_LCDTIMING2_ACB(cgdatptr->ac_bias_frequency);
    }
    else
    {
	    tmp = 0;
    }
    if (cgdatptr->invert_output_enable != 0)
    {
        tmp |= CLCDC_LCDTIMING2_IOE;
    }
    if (cgdatptr->invert_panel_clock != 0)
    {
        tmp |= CLCDC_LCDTIMING2_IPC;
    }
    if (cgdatptr->invert_hsync != 0)
    {
        tmp |= CLCDC_LCDTIMING2_IHS;
    }
    if (cgdatptr->invert_vsync != 0)
    {
        tmp |= CLCDC_LCDTIMING2_IVS;
    }

    /* Compute clocks per line based on panel type */
    switch (cgdatptr->lcd_panel_type)
    {
        case MONO_4BIT:
            /* Clocks per line is a quarter of pixels per line */
            tmp = tmp | CLCDC_LCDTIMING2_CPL((cgdatptr->pixels_per_line / 4) - 1);
            break;

        case MONO_8BIT:
            /* Clocks per line is an eighth of pixels per line */
            tmp = tmp | CLCDC_LCDTIMING2_CPL((cgdatptr->pixels_per_line / 8) - 1);
            break;

        case CSTN:
            /* CSTN Clocks per line (* 3 / 8) */
            tmp = tmp | CLCDC_LCDTIMING2_CPL(((cgdatptr->pixels_per_line * 3) / 8) - 1);
            break;
            
        case TFT:
        case ADTFT:
        case HRTFT:
        default:
            /* Clocks per line and pixels per line are the same */
            tmp = tmp | CLCDC_LCDTIMING2_CPL(cgdatptr->pixels_per_line - 1);
            break;
    }

    /* Bypass pixel clock divider */
//    tmp = tmp | CLCDC_LCDTIMING2_BCD;
    tmp = tmp | CLCDC_LCDTIMING2_PCD_LO(3);
//    tmp = tmp | CLCDC_LCDTIMING2_PCD_LO(12);
//    tmp = tmp | CLCDC_LCDTIMING2_PCD_LO(10);
//    tmp = tmp | CLCDC_LCDTIMING2_PCD_LO(5);
//    tmp = tmp | CLCDC_LCDTIMING2_PCD_LO(2);
//    tmp = tmp | CLCDC_LCDTIMING2_BCD;

    lcdptr->lcdtiming2 = tmp;

    /* Skip line end control word - just set to 0x0 */
    lcdptr->lcdtiming3 = 0x00000000;

    /* Default with all interrupts of */
    lcdptr->lcdimsc = 0x00000000;

    /* Default configuration is 16 bits per pixel with blue and blue not swapped */
    tmp = CLCDC_LCDCTRL_BPP16;
    
    /* blue and blue swapped */
    tmp |= CLCDC_LCDCTRL_BGR;

    switch (cgdatptr->lcd_panel_type)
    {
        case ADTFT:
        case HRTFT:
        case TFT:
            tmp |= CLCDC_LCDCTRL_TFT;
            break;

        case MONO_4BIT:
            tmp |= CLCDC_LCDCTRL_BW_MONO;
            break;

        case MONO_8BIT:
            tmp |= (CLCDC_LCDCTRL_MON8 | CLCDC_LCDCTRL_BW_MONO);
            break;

        case CSTN:
            ;
            break;

        default:
            /* Unsupported panel type */
            status = _ERROR;
            break;
    }

    /* Dual panel operation */
    if (cgdatptr->dual_panel == 1)
    {
        tmp |= CLCDC_LCDCTRL_DUAL;
    }

    lcdptr->lcdctrl = tmp;

    /* clear the palette (color is black )*/
    for (i = 0; i < sizeof(lcdptr->lcdpalette)/sizeof(lcdptr->lcdpalette[0]); i++)
    {
        lcdptr->lcdpalette[i] = 0;
    }

    /* setup CLCD clock CFG register */
    /* Fcclk = 72.0MHz */
    /* Fcclk = 60.0MHz */
    /* Fcclk = 57.6MHz */
    /* Fcclk = 28.8MHz */
    /* Fcclk = 11.52MHz */
    /* Fcclk = 5.76MHz */
    /* CLCDCLK is 1/1 FCCLK */
    /* CLCP is 1/10 CLCDCLK */
    /* CLCP is 1/5 CLCDCLK */
    /* CLCP is 1/2 CLCDCLK */
    /* CLCP is 1/1 CLCDCLK */
    /* Fclcp = 5.76MHz */ 
    /* Fclcp = 6.00MHz */ 
    CLCDCLKCFG = 0x0;

    return status;
}



/***********************************************************************
 *
 * Function: lcd_open
 *
 * Purpose: Open the LCD controller
 *
 * Processing:
 *     If init is not FALSE, return 0x00000000.
 *     Otherwise, return a pointer to the LCD configuration data structure.
 *
 * Parameters:
 *     ipbase: LCD descriptor device address
 *     arg   : LCD type - LCD_PARAM_T
 *
 * Outputs: None
 *
 * Returns: The pointer to a LCD config structure or 0
 *
 **********************************************************************/
INT32S lcd_open(void *lcdbase, INT32S arg)
{
    INT32S status = 0;

    if ((lcdcfg.init == FALSE) && ((CLCDC_REGS_T *) lcdbase == CLCDC))
    {
        /* Device is valid and not previously initialized */
        lcdcfg.init = TRUE;

        /* Save and return address of peripheral block */
        lcdcfg.regptr = (CLCDC_REGS_T *) lcdbase;
        lcdcfg.dptr = (LCD_PARAM_T *) arg;

        /* Disable LCD */
        lcdcfg.regptr->lcdctrl &= ~CLCDC_LCDCTRL_ENABLE;

        /* If the passed argument is not NULL, then it is a pointer
           to a LCD panel parameters structure that needs to be configured */
        if (arg != 0)
        {
            lcd_initialize(&lcdcfg);
					*(volatile INT32U *)(0xFFE10008) = 0x013F3003;
            lcd_configure_gpio();
			PWM2_InitDft();
        }

        /* Return pointer to LCD configuration data structure */
        status = (INT32S) &lcdcfg;
    }

    return status;
}

/***********************************************************************
 *
 * Function: lcd_close
 *
 * Purpose: Close the LCD controller
 *
 * Processing:
 *     If init is not TRUE, then return _ERROR to the caller as the
 *     device was not previously opened. Otherwise, disable the LCD,
 *     set init to FALSE, and return _NO_ERROR to the caller.
 *
 * Parameters:
 *     devid: Pointer to LCD config structure
 *
 * Outputs: None
 *
 * Returns: The status of the close operation
 *
 **********************************************************************/
INT32S lcd_close(INT32S devid)
{
	
    CLCDC_CFG_T *lcdcfgptr = (CLCDC_CFG_T *) devid;
    INT32S status = _ERROR;

    if (lcdcfgptr->init == TRUE)
    {
        /* 'Uninitialize' device */
        lcdcfgptr->init = FALSE;
        status = _NO_ERROR;
    }

    return status;
}

/***********************************************************************
 *
 * Function: lcd_ioctl
 *
 * Purpose: LCD configuration block
 *
 * Processing:
 *     This function is a large case block. Based on the passed function
 *     and option values, set or get the appropriate LCD
 *     parameter.
 *
 * Parameters:
 *     devid: Pointer to LCD config structure
 *     cmd:   ioctl command
 *     arg:   ioctl argument
 *
 * Outputs: None
 *
 * Returns: The status of the ioctl operation
 *
 **********************************************************************/
INT32S lcd_ioctl(INT32S devid,
                 INT32S cmd,
                 INT32S arg)
{
    CLCDC_REGS_T *lcd;
    INT32U i;
    CLCDC_CFG_T *lcdcfgptr = (CLCDC_CFG_T *) devid;
    INT32S status = _ERROR;
    
    PALETTE_ENTRY_T pal_entry, *ptr_pal_entry;
    INT8U *pal_ptr;
    INT32U *crsr_ptr;
    
    if (lcdcfgptr->init == TRUE)
    {
        status = _NO_ERROR;
        lcd = lcdcfgptr->regptr;

        switch (cmd)
        {
            case LCD_SET_BUFFER:
                /* Set LCD display frame buffer, arg = memory pointer for
                   image to be displayed */
                lcd->lcdupbase = (INT32U)arg;
                break;

            case LCD_CRSR_SET_BUFFER:
                /* Set LCD cursor image, arg = memory pointer for
                   image to be displayed */
                crsr_ptr = (INT32U *)arg;
                for(i = 0; i < 256; i++)
                {
                    lcd->cursorimage[i] = *(INT32U *)crsr_ptr;
                    crsr_ptr++;
                }
                break;

            case LCD_PWR_ON:
                /* Turn on the LCD controller power,
                   arg = 1, turn on, arg = 0, turn off */
                if (arg == 1)
                {
                        lcd_source_driver_digital_voltage_on();
                        lcd_source_driver_analog_voltage_on();
//                        lcd_gate_driver_low_voltage_on();
//                        lcd_gate_driver_high_voltage_on();
                        lcd->lcdctrl |= CLCDC_LCDCTRL_PWR;
                        lcd_backlight_on();
                }
                else if (arg == 0)
                {
                        lcd_backlight_off();
                        lcd->lcdctrl &= ~CLCDC_LCDCTRL_PWR;
//                        lcd_gate_driver_high_voltage_off();
//                        lcd_gate_driver_low_voltage_off();
                        lcd_source_driver_analog_voltage_off();
                        lcd_source_driver_digital_voltage_off();
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_ENABLE:
                /* Enable the LCD controller,
                   arg = 1, enable, arg = 0, disable */
                if (arg == 1)
                {
                        lcd->lcdctrl |= CLCDC_LCDCTRL_ENABLE;
                }
                else if (arg == 0)
                {
                        lcd->lcdctrl &= ~CLCDC_LCDCTRL_ENABLE;
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_CRSR_ENABLE:
                /* Enable the LCD cursor,
                   arg = 1, enable, arg = 0, disable */
                if (arg == 1)
                {
                        lcd->clcdcrsrctrl |= 1;
                }
                else if (arg == 0)
                {
                        lcd->clcdcrsrctrl &= ~1;
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_CRSR_NUM:
                /* Select the LCD cursor number,
                   arg = 0, 64x64, arg = 0, 1, 2, 3, 32x32 */
                lcd->clcdcrsrctrl &= ~30;
                lcd->clcdcrsrctrl |= (INT32U)arg << 3;
                break;
                
            case LCD_CRSR_SIZE:
                /* Set the LCD cursor size,
                   arg = 1, 64x64, arg = 0, 32x32 */
                if (arg == 1)
                {
                        lcd->clcdcrsrconfig |= 1;
                }
                else if (arg == 0)
                {
                        lcd->clcdcrsrconfig &= ~1;
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_CRSR_SYNC:
                /* Set the LCD cursor frame sync,
                   arg = 1, sync, arg = 0, async */
                if (arg == 1)
                {
                        lcd->clcdcrsrconfig |= 2;
                }
                else if (arg == 0)
                {
                        lcd->clcdcrsrconfig &= ~2;
                }
                else
                {
                    status = _ERROR;
                }
                break;
                
            case LCD_LOAD_PALETTE:
                /* This function supports loading of the color palette from
                   the C file generated by the bmp2c utility. It expects the
                   palette to be passed as an array of 32-bit BGR entries having
                   the following format:
                   7:3 - Blue
                   2:0 - Not used
                   15:11 - Green
                   10:8 - Not used
                   23:19 - Red
                   18:16 - Not used
                   31:24 - Not used
                   arg = pointer to input palette table address */
                ptr_pal_entry = &pal_entry;
                pal_ptr = (INT8U *) arg;

                /* 256 entry in the palette table */
                for(i = 0; i < 256/2; i++)
                {
                    pal_entry.Bl = (*pal_ptr++) >> 3;  /* blue first */
                    pal_entry.Gl = (*pal_ptr++) >> 3;  /* get green */
                    pal_entry.Rl = (*pal_ptr++) >> 3;  /* get red */
                    pal_ptr++;      /* skip over the unused byte */
                    /* do the most significant halfword of the palette */
                    pal_entry.Bu = (*pal_ptr++) >> 3;  /* blue first */
                    pal_entry.Gu = (*pal_ptr++) >> 3;  /* get green */
                    pal_entry.Ru = (*pal_ptr++) >> 3;  /* get red */
                    pal_ptr++;      /* skip over the unused byte */

                    lcd->lcdpalette[i] = *(INT32U *)ptr_pal_entry;
                }
                break;

            case LCD_CRSR_LOAD_PALETTE0:
                /* 7:0 - Red
                   15:8 - Green
                   23:16 - Blue
                   31:24 - Not used*/
                lcd->clcdcrsrpalette0 = (INT32U)arg;
                break;

            case LCD_CRSR_LOAD_PALETTE1:
                /* 7:0 - Red
                   15:8 - Green
                   23:16 - Blue
                   31:24 - Not used*/
                lcd->clcdcrsrpalette1 = (INT32U)arg;
                break;

            case LCD_SET_BPP:
                /* Set current display bits per pixel, arg = bits per pixel */
                switch (arg)
                {
                    case BPP_IS_1:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP1;
                        break;
                    case BPP_IS_2:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP2;
                        break;
                    case BPP_IS_4:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP4;
                        break;
                    case BPP_IS_8:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP8;
                        break;
                    case BPP_IS_16:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP16;
                        break;
                    case BPP_IS_24:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP24;
                        break;
                    case BPP_IS_16_565_MODE:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP16_565_MODE;
                        break;
                    case BPP_IS_12_444_MODE:
                        lcd->lcdctrl &= ~_SBF(1, _BITMASK(3));
                        lcd->lcdctrl |= CLCDC_LCDCTRL_BPP12_444_MODE;
                        break;
                    default:
                        status = _ERROR;
                        break;
                }
                break;

            case LCD_SET_BGR:
                /* LCD invert the bgr bit in the LCD controller. arg = 1, invert
                   BGR for reverse color, arg = 0, BGR for normal color */
                if (arg == 1)
                {
                    /*  
                     *   Palette and direct color storage is 
                     *   blue in bits 4-0,
                     *   green in bits 9-5,
                     *   red in bits 14-10,
                     *   intensity in bit 15.
                     */
                    lcd->lcdctrl |= CLCDC_LCDCTRL_BGR;
                }
                else if (arg == 0)
                {
                    /*
                     *   Palette and direct color storage is 
                     *   red in bits 4-0,
                     *   green in bits 9-5,
                     *   blue in bits 14-10,
                     *   intensity in bit 15.
                     */
                    lcd->lcdctrl &= ~CLCDC_LCDCTRL_BGR;
                    
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_SET_INTERRUPT:
                /* Set interrupt mask set/clear register */
                if (arg == CLCDC_LCD_INTERRUPT_FUF)
                {
                    lcd->lcdimsc |= CLCDC_LCD_INTERRUPT_FUF;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_LNBU)
                {
                    lcd->lcdimsc |= CLCDC_LCD_INTERRUPT_LNBU;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_VCOMP)
                {
                    lcd->lcdimsc |= CLCDC_LCD_INTERRUPT_VCOMP;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_MBERROR)
                {
                    lcd->lcdimsc |= CLCDC_LCD_INTERRUPT_MBERROR;
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_CLR_INTERRUPT:
                /* Set interrupt clear register*/
                if (arg == CLCDC_LCD_INTERRUPT_FUF)
                {
                    lcd->lcdicr |= CLCDC_LCD_INTERRUPT_FUF;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_LNBU)
                {
                    lcd->lcdicr |= CLCDC_LCD_INTERRUPT_LNBU;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_VCOMP)
                {
                    lcd->lcdicr |= CLCDC_LCD_INTERRUPT_VCOMP;
                }
                else if (arg == CLCDC_LCD_INTERRUPT_MBERROR)
                {
                    lcd->lcdicr |= CLCDC_LCD_INTERRUPT_MBERROR;
                }
                else
                {
                    status = _ERROR;
                }
                break;

            case LCD_CRSR_SET_INTERRUPT:
                /* Set cursor interrupt mask set/clear register */
                lcd->lcdcrsrimsc |= 1;
                break;

            case LCD_CRSR_CLR_INTERRUPT:
                /* Set cursor interrupt clear register*/
                lcd->lcdcrsricr |= 1;
                break;

            case LCD_CRSR_XY:
                /* Set lcd cursor xy position register*/
                lcd->clcdcrsrxy = (INT32U)arg;
                break;

            case LCD_CRSR_CLIP:
                /* Set lcd cursor clip position register*/
                lcd->clcdcrsrclip = (INT32U)arg;
                break;

            case LCD_GET_STATUS:
                switch (arg)
                {
                    case LCD_GET_BUFFER:
                        /* Returns LCD fram buffer address */
                        status = (INT32S)lcd->lcdupbase;
                        break;
                        
                    case LCD_GET_BPP:
                        /* Returns current LCD panel bit per pixel */
                        i = (lcd->lcdctrl) & _SBF(1,_BITMASK(3) );
                        switch (i)
                        {
                            case CLCDC_LCDCTRL_BPP1:
                                status = BPP_IS_1;
                                break;
                            case CLCDC_LCDCTRL_BPP2:
                                status = BPP_IS_2;
                                break;
                            case CLCDC_LCDCTRL_BPP4:
                                status = BPP_IS_4;
                                break;
                            case CLCDC_LCDCTRL_BPP8:
                                status = BPP_IS_8;
                                break;
                            case CLCDC_LCDCTRL_BPP16:
                                status = BPP_IS_16;
                                break;
                            case CLCDC_LCDCTRL_BPP24:
                                status = BPP_IS_24;
                                break;
                            case CLCDC_LCDCTRL_BPP16_565_MODE:
                                status = BPP_IS_16_565_MODE;
                                break;
                            case CLCDC_LCDCTRL_BPP12_444_MODE:
                                status = BPP_IS_12_444_MODE;
                                break;
                            default:
                                status = _ERROR;
                                break;
                        }
                        break;
                        
                    case LCD_GET_PALETTE:
                        /* Returns a pointer to palette table */
                        status = (INT32S)lcd->lcdpalette;
                        break;

                    case LCD_CRSR_GET_PALETTE0:
                        /* Returns a pointer to cursor palette table */
                        status = (INT32S)lcd->clcdcrsrpalette0;
                        break;

                    case LCD_CRSR_GET_PALETTE1:
                        /* Returns a pointer to cursor palette table */
                        status = (INT32S)lcd->clcdcrsrpalette1;
                        break;

                    case LCD_GET_INTERRUPT:
                        /* Get interrupt mask sstatus register */
                        status = (INT32S)lcd->lcdmis;
                        break;

                    case LCD_CRSR_GET_INTERRUPT:
                        /* Get cursor interrupt mask sstatus register */
                        status = (INT32S)lcd->lcdcrsrmis;
                        break;

                    default:
                        /* Unsupported parameter */
                        status = _ERROR;
                        break;
                        
                }
                break;

            default:
                /* Unsupported parameter */
                status = _ERROR;
        }
    }

    return status;
}
