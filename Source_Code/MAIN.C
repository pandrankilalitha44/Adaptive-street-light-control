//---------------------------------------------------------
// Section: Header Files
// Include the device definitions and project modules required
// for the LCD, RTC, LDR, ADC, keypad, delays, and interrupts.
//---------------------------------------------------------
#include <LPC21xx.h>
#include "lcd.h"
#include "rtc.h"
#include "LDR.h"
#include "adc.h"
#include "lcd_defines.h"
#include "types.h"
#include "kpm.h"
#include "delay.h"
#include "interrupt.h"
#include "defines.h"
//---------------------------------------------------------
// Section: Hardware and Global Variables
// LED identifies the GPIO output pin. The global variables
// hold menu state, RTC values, and schedule boundaries.
//---------------------------------------------------------
#define  LED 5
u32 menu_flag;
u32 hour,min,sec,date,month,year,day,hr_start,hr_stop,min_start,min_stop;
enum days{SUN,MON,TUE,WED,THU,FRI,SAT};
//---------------------------------------------------------
// Section: LCD Symbols and Schedule Defaults
// The lookup tables define custom LCD characters for the
// LED status. The following values define the default
// operating schedule.
//---------------------------------------------------------
const u8 CgramLUT1[8]={0x00,0x0E,0X1F,0X1F,0X1F,0X0E,0X00,0X00};
u8 CgramLUT2[8]={0x00,0x0E,0X11,0X11,0X11,0X0E, 0X00,0X00};
u32 Hr_START=18;
u32 Hr_STOP=6;
u32 MIN_START=0;
u32 MIN_STOP=0;
extern u16 adc;
extern f32 volt,Rldr,lux;
int main()
//---------------------------------------------------------
// Function: main
// Purpose : Initialize the peripherals and continuously
//           monitor the RTC and LDR to control the LED.
// Returns : The embedded application runs continuously.
//---------------------------------------------------------
{
                // Configure the LED pin as an output.
                IODIR0|=1<<LED;
                // Start with the LED switched OFF.
                IOCLR0=1<<LED;
        // Initialize the real-time clock peripheral.
        RTC_Init();
        // Initialize the LCD interface.
        InitLCD();
        // Initialize the keypad interface.
            InitKPM();
        // Initialize external interrupt 0.
                InitEINT0();
        // Set the initial RTC time.
        SetRTCTimeInfo(19,44,0);
        // Set the initial RTC date.
        SetRTCDateInfo(21,4,2026);
        // Set the initial day of the week.
        SetRTCDay(TUE);
        // Continuously refresh the display and evaluate the LED condition.
        while(1)
        {
                // Enable the LCD display and hide the cursor.
                            CmdLCD(DSP_ON_CUR_OFF);
                // Read the current RTC time and display it.
                GetRTCTimeInfo(&hour,&min,&sec);
                DisplayRTCTime(hour,min,sec);
                // Read the current date and display it.
                GetRTCDateInfo(&date,&month,&year);
                DisplayRTCDate(date,month,year);
                // Read the current day and display it.
                GetRTCDay(&day);
                DisplayRTCDay(day);
                // Read the LDR value and calculate voltage, resistance, and lux.
                Read_LDR(&adc,&volt,&Rldr,&lux);
                if(Iswithintime()==1)
                // Check whether the current time is within the operating schedule.
                {
                        if(lux<300)
                        // If ambient light is below the threshold, switch the LED ON.
                        {
                                // Load the custom character used for the ON status.
                                BuildCGRAM((u8*)CgramLUT1,8);
                                                    CmdLCD(GOTO_LINE2_POS0+12);
                                                            CharLCD(0);
                                CmdLCD(GOTO_LINE2_POS0+13);
                                StrLCD("ON ");
                                                                 // Set the LED output HIGH.
                                                                IOSET0=1<<LED;
                        }
                        else
                        {
                                // Load the custom character used for the OFF status.
                                BuildCGRAM((u8*)CgramLUT2,8);
                                                    CmdLCD(GOTO_LINE2_POS0+12);
                                                                CharLCD(0);
                                CmdLCD(GOTO_LINE2_POS0+13);
                                StrLCD("OFF");
                                                            // Clear the LED output to switch it OFF.
                                                            IOCLR0=1<<LED;
                        }
                }
                                else
                                {
                                        // Outside the schedule, keep the LED switched OFF.
                                        IOCLR0=1<<LED;
                                        CmdLCD(GOTO_LINE2_POS0+13);
                    StrLCD("OFF");

                                }
                                                                //delay_ms(100);

                // Open the settings menu when menu_flag is set.
                if(menu_flag==1)
                {
                  // Clear the display before entering the menu.
                  CmdLCD(CLEAR_LCD);
                  // Run the menu editor to modify application settings.
                  EditMenu();
                                  CmdLCD(CLEAR_LCD);
                                   // Reset the menu flag after the menu exits.
                                  menu_flag=0;
                }

                                }
}
  