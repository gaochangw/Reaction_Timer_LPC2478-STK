#include "io_macros.h"
/* Pin function select register 0 */
typedef struct{
__REG32 P0_0   : 2;
__REG32 P0_1   : 2;
__REG32 P0_2   : 2;
__REG32 P0_3   : 2;
__REG32 P0_4   : 2;
__REG32 P0_5   : 2;
__REG32 P0_6   : 2;
__REG32 P0_7   : 2;
__REG32 P0_8   : 2;
__REG32 P0_9   : 2;
__REG32 P0_10  : 2;
__REG32 P0_11  : 2;
__REG32 P0_12  : 2;
__REG32 P0_13  : 2;
__REG32 P0_14  : 2;
__REG32 P0_15  : 2;
} __pinsel0_bits;

typedef struct{
__REG32 P0_16  : 2;
__REG32 P0_17  : 2;
__REG32 P0_18  : 2;
__REG32 P0_19  : 2;
__REG32 P0_20  : 2;
__REG32 P0_21  : 2;
__REG32 P0_22  : 2;
__REG32 P0_23  : 2;
__REG32 P0_24  : 2;
__REG32 P0_25  : 2;
__REG32 P0_26  : 2;
__REG32 P0_27  : 2;
__REG32 P0_28  : 2;
__REG32 P0_29  : 2;
__REG32 P0_30  : 2;
__REG32 P0_31  : 2;
} __pinsel1_bits;

/* Pin function select register 2 */
typedef struct{
__REG32 P1_0   : 2;
__REG32 P1_1   : 2;
__REG32 P1_2   : 2;
__REG32 P1_3   : 2;
__REG32 P1_4   : 2;
__REG32 P1_5   : 2;
__REG32 P1_6   : 2;
__REG32 P1_7   : 2;
__REG32 P1_8   : 2;
__REG32 P1_9   : 2;
__REG32 P1_10  : 2;
__REG32 P1_11  : 2;
__REG32 P1_12  : 2;
__REG32 P1_13  : 2;
__REG32 P1_14  : 2;
__REG32 P1_15  : 2;
} __pinsel2_bits;

/* Pin function select register 3 */
typedef struct{
__REG32 P1_16  : 2;
__REG32 P1_17  : 2;
__REG32 P1_18  : 2;
__REG32 P1_19  : 2;
__REG32 P1_20  : 2;
__REG32 P1_21  : 2;
__REG32 P1_22  : 2;
__REG32 P1_23  : 2;
__REG32 P1_24  : 2;
__REG32 P1_25  : 2;
__REG32 P1_26  : 2;
__REG32 P1_27  : 2;
__REG32 P1_28  : 2;
__REG32 P1_29  : 2;
__REG32 P1_30  : 2;
__REG32 P1_31  : 2;
} __pinsel3_bits;

/* Pin function select register 4 */
typedef struct{
__REG32 P2_0   : 2;
__REG32 P2_1   : 2;
__REG32 P2_2   : 2;
__REG32 P2_3   : 2;
__REG32 P2_4   : 2;
__REG32 P2_5   : 2;
__REG32 P2_6   : 2;
__REG32 P2_7   : 2;
__REG32 P2_8   : 2;
__REG32 P2_9   : 2;
__REG32 P2_10  : 2;
__REG32 P2_11  : 2;
__REG32 P2_12  : 2;
__REG32 P2_13  : 2;
__REG32 P2_14  : 2;
__REG32 P2_15  : 2;
} __pinsel4_bits;

/* Pin function select register 5 */
typedef struct{
__REG32 P2_16  : 2;
__REG32 P2_17  : 2;
__REG32 P2_18  : 2;
__REG32 P2_19  : 2;
__REG32 P2_20  : 2;
__REG32 P2_21  : 2;
__REG32 P2_22  : 2;
__REG32 P2_23  : 2;
__REG32 P2_24  : 2;
__REG32 P2_25  : 2;
__REG32 P2_26  : 2;
__REG32 P2_27  : 2;
__REG32 P2_28  : 2;
__REG32 P2_29  : 2;
__REG32 P2_30  : 2;
__REG32 P2_31  : 2;
} __pinsel5_bits;

/* Pin function select register 6 */
typedef struct{
__REG32 P3_0   : 2;
__REG32 P3_1   : 2;
__REG32 P3_2   : 2;
__REG32 P3_3   : 2;
__REG32 P3_4   : 2;
__REG32 P3_5   : 2;
__REG32 P3_6   : 2;
__REG32 P3_7   : 2;
__REG32 P3_8   : 2;
__REG32 P3_9   : 2;
__REG32 P3_10  : 2;
__REG32 P3_11  : 2;
__REG32 P3_12  : 2;
__REG32 P3_13  : 2;
__REG32 P3_14  : 2;
__REG32 P3_15  : 2;
} __pinsel6_bits;

/* Pin function select register 7 */
typedef struct{
__REG32 P3_16  : 2;
__REG32 P3_17  : 2;
__REG32 P3_18  : 2;
__REG32 P3_19  : 2;
__REG32 P3_20  : 2;
__REG32 P3_21  : 2;
__REG32 P3_22  : 2;
__REG32 P3_23  : 2;
__REG32 P3_24  : 2;
__REG32 P3_25  : 2;
__REG32 P3_26  : 2;
__REG32 P3_27  : 2;
__REG32 P3_28  : 2;
__REG32 P3_29  : 2;
__REG32 P3_30  : 2;
__REG32 P3_31  : 2;
} __pinsel7_bits;

/* Pin function select register 8 */
typedef struct{
__REG32 P4_0   : 2;
__REG32 P4_1   : 2;
__REG32 P4_2   : 2;
__REG32 P4_3   : 2;
__REG32 P4_4   : 2;
__REG32 P4_5   : 2;
__REG32 P4_6   : 2;
__REG32 P4_7   : 2;
__REG32 P4_8   : 2;
__REG32 P4_9   : 2;
__REG32 P4_10  : 2;
__REG32 P4_11  : 2;
__REG32 P4_12  : 2;
__REG32 P4_13  : 2;
__REG32 P4_14  : 2;
__REG32 P4_15  : 2;
} __pinsel8_bits;

/* Pin function select register 9 */
typedef struct{
__REG32 P4_16  : 2;
__REG32 P4_17  : 2;
__REG32 P4_18  : 2;
__REG32 P4_19  : 2;
__REG32 P4_20  : 2;
__REG32 P4_21  : 2;
__REG32 P4_22  : 2;
__REG32 P4_23  : 2;
__REG32 P4_24  : 2;
__REG32 P4_25  : 2;
__REG32 P4_26  : 2;
__REG32 P4_27  : 2;
__REG32 P4_28  : 2;
__REG32 P4_29  : 2;
__REG32 P4_30  : 2;
__REG32 P4_31  : 2;
} __pinsel9_bits;
                              
/* A/D Control Register */

typedef struct{
__REG32 SEL     : 8;
__REG32 CLKDIV  : 8;
__REG32 BURST   : 1;
__REG32 CLKS    : 3;
__REG32         : 1;
__REG32 PDN     : 1;
__REG32         : 2;
__REG32 START   : 3;
__REG32 EDGE    : 1;
__REG32         : 4;
} __adcr_bits;

/* A/D Global Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         : 8;
__REG32 CHN     : 3;
__REG32         : 3;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __adgdr_bits;

/* A/D Status Register */
typedef struct{
__REG32 DONE0     : 1;
__REG32 DONE1     : 1;
__REG32 DONE2     : 1;
__REG32 DONE3     : 1;
__REG32 DONE4     : 1;
__REG32 DONE5     : 1;
__REG32 DONE6     : 1;
__REG32 DONE7     : 1;
__REG32 OVERRUN0  : 1;
__REG32 OVERRUN1  : 1;
__REG32 OVERRUN2  : 1;
__REG32 OVERRUN3  : 1;
__REG32 OVERRUN4  : 1;
__REG32 OVERRUN5  : 1;
__REG32 OVERRUN6  : 1;
__REG32 OVERRUN7  : 1;
__REG32 ADINT     : 1;
__REG32           :15;
} __adstat_bits;

/* A/D Intrrupt Enable Register */
typedef struct{
__REG32 ADINTEN0  : 1;
__REG32 ADINTEN1  : 1;
__REG32 ADINTEN2  : 1;
__REG32 ADINTEN3  : 1;
__REG32 ADINTEN4  : 1;
__REG32 ADINTEN5  : 1;
__REG32 ADINTEN6  : 1;
__REG32 ADINTEN7  : 1;
__REG32 ADGINTEN  : 1;
__REG32           :23;
} __adinten_bits;

/* A/D Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         :14;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __addr_bits;

/* Power control for peripherals register */
typedef struct{
__REG32             : 1;
__REG32 PCTIM0      : 1;
__REG32 PCTIM1      : 1;
__REG32 PCUART0     : 1;
__REG32 PCUART1     : 1;
__REG32 PCPWM0      : 1;
__REG32 PCPWM1      : 1;
__REG32 PCI2C0      : 1;
__REG32 PCSPI       : 1;
__REG32 PCRTC       : 1;
__REG32 PCSSP1      : 1;
__REG32 PCEMC       : 1;
__REG32 PCAD        : 1;
__REG32 PCAN1       : 1;
__REG32 PCAN2       : 1;
__REG32             : 4;
__REG32 PCI2C1      : 1;
__REG32 PCLCD       : 1;
__REG32 PCSSP0      : 1;
__REG32 PCTIM2      : 1;
__REG32 PCTIM3      : 1;
__REG32 PCUART2     : 1;
__REG32 PCUART3     : 1;
__REG32 PCI2C2      : 1;
__REG32 PCI2S       : 1;
__REG32 PCSDC       : 1;
__REG32 PCGPDMA     : 1;
__REG32 PCENET      : 1;
__REG32 PCUSB       : 1;
} __pconp_bits;


/* GPIO 0 Registers */
typedef struct {
__REG32 P0_0   : 1;
__REG32 P0_1   : 1;
__REG32 P0_2   : 1;
__REG32 P0_3   : 1;
__REG32 P0_4   : 1;
__REG32 P0_5   : 1;
__REG32 P0_6   : 1;
__REG32 P0_7   : 1;
__REG32 P0_8   : 1;
__REG32 P0_9   : 1;
__REG32 P0_10  : 1;
__REG32 P0_11  : 1;
__REG32 P0_12  : 1;
__REG32 P0_13  : 1;
__REG32 P0_14  : 1;
__REG32 P0_15  : 1;
__REG32 P0_16  : 1;
__REG32 P0_17  : 1;
__REG32 P0_18  : 1;
__REG32 P0_19  : 1;
__REG32 P0_20  : 1;
__REG32 P0_21  : 1;
__REG32 P0_22  : 1;
__REG32 P0_23  : 1;
__REG32 P0_24  : 1;
__REG32 P0_25  : 1;
__REG32 P0_26  : 1;
__REG32 P0_27  : 1;
__REG32 P0_28  : 1;
__REG32 P0_29  : 1;
__REG32 P0_30  : 1;
__REG32 P0_31  : 1;
} __gpio0_bits;

#if 0
#ifdef PINSEL0_BIT
    extern __pinsel0_bits *PINSEL0_bit;
#else   
#define PINSEL0_BIT  
	__pinsel0_bits *PINSEL0_bit;
#endif
#ifdef PINSEL1_BIT
    extern __pinsel1_bits *PINSEL1_bit;
#else    
#define PINSEL1_BIT 
	__pinsel1_bits *PINSEL1_bit;
#endif
#ifdef PINSEL3_BIT
   extern __pinsel3_bits *PINSEL3_bit;
#else   
#define PINSEL3_BIT
	__pinsel3_bits *PINSEL3_bit;
#endif
#ifdef AD0CR_BIT
    extern __adcr_bits * AD0CR_bit; 
#else    
#define AD0CR_BIT
    __adcr_bits * AD0CR_bit;
#endif
#ifdef AD0GDR_BIT
   extern __adgdr_bits * AD0GDR_bit;
#else   
#define AD0GDR_BIT
	__adgdr_bits * AD0GDR_bit;
#endif
#ifdef PCONP_BIT
   extern __pconp_bits * PCONP_bit;
#else   
#define PCONP_BIT
    __pconp_bits * PCONP_bit;
#endif
#ifdef PINMODE1_BIT
   extern __pinsel1_bits *PINMODE1_bit;
#else   
#define PINMODE1_BIT
	__pinsel1_bits *PINMODE1_bit;
#endif
#ifdef __gpio0_bits
    extern __gpio0_bits *FIO0DIR_bit;
#else    
	__gpio0_bits *FIO0DIR_bit;
#endif
#endif

