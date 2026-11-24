//---------------------------------------------------------
// Header File Inclusions
//---------------------------------------------------------
// LPC21xx.h    = Provides LPC21xx microcontroller register definitions
// types.h      = Defines user-defined data types
// rtc.h        = Provides RTC-related declarations
// lcd.h        = Provides LCD interface function declarations
// lcd_defines.h= Contains LCD command and position definitions
// delay.h      = Provides delay function declarations
// kpm.h        = Provides keypad interface function declarations
#include <LPC21xx.h>
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "kpm.h"
//---------------------------------------------------------
// External Interrupt 0 (EINT0) Configuration
//---------------------------------------------------------
// Defines the pin selection and VIC channel details for EINT0.
// EINT0_PIN_0_1 = Function selection code for the EINT0 pin
// EINT0_PIN_FUNC = PINSEL register configuration value
// EINT0_VIC_CHNO = VIC interrupt channel number assigned to EINT0
#define EINT0_PIN_0_1 0
#define EINT0_PIN_FUNC 0x25400000
#define EINT0_VIC_CHNO 17
// External variable used to indicate that the menu action
// has been requested by the external interrupt.
extern  u32 menu_flag;
//---------------------------------------------------------
// Function: eint0_isr
// Interrupt Service Routine for External Interrupt 0.
// Sets the menu flag, clears the EINT0 interrupt flag,
// and informs the VIC that interrupt processing is complete.
//---------------------------------------------------------
void eint0_isr(void)__irq
{
        menu_flag=1;
        EXTINT=1<<0;
        VICVectAddr=0;
}

//---------------------------------------------------------
// Function: InitEINT0
// Configures the EINT0 pin, registers its interrupt service
// routine with the VIC, enables the interrupt, and selects
// the external interrupt triggering mode.
//---------------------------------------------------------
void InitEINT0(void)
{
PINSEL1&=~(3<<((30-16)*2));
PINSEL1|=EINT0_PIN_FUNC;
		VICVectCntl0=(1<<5)| EINT0_VIC_CHNO;
VICIntEnable=1<<EINT0_VIC_CHNO;

VICVectAddr0=(unsigned)eint0_isr;

//EXTINT=0;
EXTMODE=1<<3;
//EXTPOLAR=0;
}

