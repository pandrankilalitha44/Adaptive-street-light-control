//---------------------------------------------------------
// Header File Inclusions
//---------------------------------------------------------
// LPC21xx.h    = Provides LPC21xx microcontroller register definitions
// rtc.h        = Provides RTC function declarations
// lcd.h        = Provides LCD interface function declarations
// lcd_defines.h= Contains LCD command and position definitions
// delay.h      = Provides delay function declarations
// kpm.h        = Provides keypad interface function declarations
#include <LPC21xx.h>
#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "kpm.h"
extern u32 hour,min,sec,date,month,year,day,hr_start,hr_stop,min_start,min_stop;

//---------------------------------------------------------
// Global Variables and Day Lookup Table
//---------------------------------------------------------
// Stores the abbreviated names of the seven days of the week.
// External variables hold RTC values and schedule settings.
// lastKey stores the most recently pressed keypad key.
//---------------------------------------------------------
s8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
extern u32 Hr_START,Hr_STOP,MIN_START,MIN_STOP;
u8 lastKey;
#include "lcd.h"
#include "lcd_defines.h"

//---------------------------------------------------------
// RTC Clock Configuration
//---------------------------------------------------------
// FOSC       = External oscillator frequency
// CCLK       = CPU clock frequency
// PCLK       = Peripheral clock frequency
// PREINT_VAL = RTC prescaler integer value
// PREFRAC_VAL= RTC prescaler fractional value
//---------------------------------------------------------
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int) ((PCLK/32768)-1))
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

//---------------------------------------------------------
// RTC Control Register Bit Definitions
//---------------------------------------------------------
// RTC_ENABLE = Enables the Real-Time Clock
// RTC_RESET  = Resets the RTC prescaler
// RTC_CLKSRC = Selects the RTC clock source
//---------------------------------------------------------
#define RTC_ENABLE (1<<0)
#define RTC_RESET (1<<1)
#define RTC_CLKSRC (1<<4)


//---------------------------------------------------------
// Target Controller Selection
//---------------------------------------------------------
// Defines the supported controller options and selects
// LPC2148 as the target CPU for conditional RTC setup.
//---------------------------------------------------------
#define LPC2129 0
#define LPC2148 1
#define CPU LPC2148
//---------------------------------------------------------
// Function: RTC_Init
// Resets and enables the RTC. The prescaler registers are
// configured for LPC2129, while the RTC clock source is
// selected for LPC2148.
//---------------------------------------------------------
void RTC_Init(void)
{
        CCR=RTC_RESET;
        #if(CPU==LPC2129)
        PREINT=PREINT_VAL;
        PREFRAC=PREFRAC_VAL;
        CCR=RTC_ENABLE;
        #elif(CPU==LPC2148)
        CCR=RTC_ENABLE | RTC_CLKSRC;
        #endif
}
//---------------------------------------------------------
// Function: GetRTCTimeInfo
// Reads the current hour, minute, and second values from RTC.
// hour   = Pointer to store the hour value
// minute = Pointer to store the minute value
// second = Pointer to store the second value
//---------------------------------------------------------
void GetRTCTimeInfo(u32 *hour,u32 *minute,u32 *second)
{
        *hour=HOUR;
        *minute=MIN;
        *second=SEC;
}
//---------------------------------------------------------
// Function: DisplayRTCTime
// Displays the supplied time on the first LCD line in
// HH:MM:SS format.
//---------------------------------------------------------
void DisplayRTCTime(u32 hour,u32 minute,u32 second)
{
        CmdLCD(GOTO_LINE1_POS0);
        CharLCD((hour/10)+48);
        CharLCD((hour%10)+48);
        CharLCD(':');
        CharLCD((minute/10)+0x30);
        CharLCD((minute%10)+0x30);
        CharLCD(':');
        CharLCD((second/10)+'0');
        CharLCD((second%10)+'0');
}
//---------------------------------------------------------
// Function: GetRTCDateInfo
// Reads the current date, month, and year values from RTC.
// date  = Pointer to store the date
// month = Pointer to store the month
// year  = Pointer to store the year
//---------------------------------------------------------
void GetRTCDateInfo(u32 *date,u32 *month,u32 *year)
{
   *date=DOM;
   *month=MONTH;
   *year=YEAR;
}
//---------------------------------------------------------
// Function: DisplayRTCDate
// Displays the supplied date on the second LCD line in
// DD/MM/YYYY format.
//---------------------------------------------------------
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
        CmdLCD(GOTO_LINE2_POS0);
        CharLCD((date/10)+48);
        CharLCD((date%10)+48);
                                CharLCD('/');
        CharLCD((month/10)+0x30);
        CharLCD((month%10)+0x30);
              CharLCD('/');
        u32LCD(year);
}
//---------------------------------------------------------
// Function: SetRTCTimeInfo
// Updates the RTC hour, minute, and second registers.
//---------------------------------------------------------
void SetRTCTimeInfo(u32 hour,u32 minute,u32 second)
{
        HOUR=hour;
        MIN=minute;
        SEC=second;
}
//---------------------------------------------------------
// Function: SetRTCDateInfo
// Updates the RTC date, month, and year registers.
//---------------------------------------------------------
void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
   DOM=date;
   MONTH=month;
   YEAR=year;
}
//---------------------------------------------------------
// Function: GetRTCDay
// Reads the current day-of-week value from the RTC.
// day = Pointer to store the day value
//---------------------------------------------------------
void GetRTCDay(u32 *day)
{
        *day=DOW;
}
//---------------------------------------------------------
// Function: DisplayRTCDay
// Displays the abbreviated day name using the week lookup table.
//---------------------------------------------------------
void DisplayRTCDay(u32 day)
{
        CmdLCD(GOTO_LINE1_POS0+11);
        StrLCD(week[day]);
}
//---------------------------------------------------------
// Function: SetRTCDay
// Updates the RTC day-of-week register.
//---------------------------------------------------------
void SetRTCDay(u32 day)
{
        DOW=day;
}
//---------------------------------------------------------
// Function: RTC_EDIT
// Displays the RTC edit menu and accepts keypad input to
// update hour, minute, second, date, month, year, or day.
// Validates each entered value before saving it to the RTC.
// Option 8 exits the RTC edit menu.
//---------------------------------------------------------
void RTC_EDIT()
{
          u8 key;
          while(1)
          {
                CmdLCD(CLEAR_LCD);
          StrLCD("1.H 2.M 3.S 4.D");
          //delay_ms(300);
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("5.m 6.Y 7.d 8.E");

                key=keyscan();
                 delay_ms(300);
                if(key=='1')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter hour");
                                        delay_ms(500);
                                        ReadTime(&hour,&lastKey);
                                        if(hour<=23 )
                                        {
                                                HOUR=hour;
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("hour saved");
                                                delay_ms(500);
                                                CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                 CmdLCD(GOTO_LINE2_POS0);
                                                 StrLCD("Invalid ");
                                                 delay_ms(500);
                                        }
                }
                if(key=='2')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter min");
                                        delay_ms(500);
                                        ReadTime(&min,&lastKey);
                                        if(min<=59)
                                        {
                                                MIN=min;
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("min saved");
                                                delay_ms(500);
                                                CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                 CmdLCD(GOTO_LINE2_POS0);
                                                 StrLCD("Invalid ");
                                                 delay_ms(500);
                                        }
                }
                if(key=='3')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter sec");
                                        ReadTime(&sec,&lastKey);
                                        if(sec<=59)
                                        {
                                                SEC=sec;
                                                CmdLCD(GOTO_LINE2_POS0);
                                                StrLCD("seconds saved");
                                                delay_ms(500);
                                                CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("Invlaid");
                                                        delay_ms(500);
                                        }
                }
                if(key=='4')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter date");
                                        ReadTime(&date,&lastKey);
                                        if(date<=31)
                                        {
                                                                        DOM=date;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("Date saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("Invlaid");
                                                        delay_ms(500);
                                        }
                }
                if(key=='5')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter mon");
                                        delay_ms(500);
                                        ReadTime(&month,&lastKey);
                                        if(month<=12)
                                        {
                                                                        MONTH=month;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("MONTH saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("Invlaid");
                                                        delay_ms(500);
                                        }
                }
                if(key=='6')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter YEAR");
                                        ReadYear(&year,&lastKey);
                                        if(year<=4095)
                                        {
                                                                        YEAR=year;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("year saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("Invlaid");
                                                        delay_ms(500);
                                        }
                }
                if(key=='7')
                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("Enter day");
                                        ReadTime(&day,&lastKey);
                                        if(day<=6)
                                        {
                                                                        DOW=day;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("day saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                        }
                                        else
                                        {
                                                        CmdLCD(GOTO_LINE2_POS0);
                                                        StrLCD("Invlaid");
                                                        delay_ms(500);
                                        }
                }
                if(key=='8')
                {
                        return;
                }
                }
                //CmdLCD(CLEAR_LCD);
}
//---------------------------------------------------------
// Function: SCHEDULE_EDIT
// Displays the schedule edit menu and accepts keypad input
// to update the schedule start and stop hours and minutes.
// Validates each entered value before saving it.
// Option 3 exits the schedule edit menu.
//---------------------------------------------------------
void SCHEDULE_EDIT()
{
                                u8 key;
                                while(1)
                                {
                                        CmdLCD(CLEAR_LCD);
                                        StrLCD("1.HrS 2.MnS 3.E");
                            //delay_ms(300);
                                        CmdLCD(GOTO_LINE2_POS0);
                                        StrLCD("4.Hrs 5.Mns");
                                   key=keyscan();
                                   delay_ms(300);
                         if(key=='1')
                         {
                                                 CmdLCD(CLEAR_LCD);
                                                 StrLCD("Enter HrSTART");
                                                 delay_ms(500);
                                                 ReadTime(&hr_start,&lastKey);
                                                 if(hr_start>=16 && hr_start<=23)
                                                 {
                                                                Hr_START=hr_start;
                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                StrLCD("hr_start saved");
                                                                delay_ms(500);
                                                                CmdLCD(CLEAR_LCD);
                                                        }
                                                        else
                                                        {
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("Invalid");
                                                                        delay_ms(500);
                                                        }
                                }
                         if(key=='2')
                         {
                                                CmdLCD(CLEAR_LCD);
                                                StrLCD("Enter MINSTART");
                                                delay_ms(500);
                                                 ReadTime(&min_start,&lastKey);
                                                 if(min_start>0 && min_start<=59)
                                                 {
                                                                MIN_START=min_start;
                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                StrLCD("minstart saved");
                                                                delay_ms(500);
                                                                CmdLCD(CLEAR_LCD);
                                                        }
                                                        else
                                                        {
                                                                CmdLCD(GOTO_LINE2_POS0);
                                                                StrLCD("Invalid");
                                                                delay_ms(500);
                                                        }
                                }
                                if(key=='3')
                                {
                                        return;
                                }
                         if(key=='4')
                         {
                                                        CmdLCD(CLEAR_LCD);
                                                        StrLCD("Enter HrSTOP");
                                                        delay_ms(500);
                                                        ReadTime(&hr_stop,&lastKey);
                                                        if(hr_stop>=5 && hr_stop<=7 )
                                                        {
                                                                        Hr_STOP=hr_stop;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("hrstop saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                                        }
                                                        else
                                                        {
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("Invalid");
                                                                        delay_ms(500);
                                                        }
                         }
                         if(key=='5')
                         {
                                                        CmdLCD(CLEAR_LCD);
                                                        StrLCD("Enter MINSTOP");
                                                        delay_ms(500);
                                                        ReadTime(&min_stop,&lastKey);
                                                        if(min_stop>0 && min_stop<=59)
                                                        {
                                                                        MIN_STOP=min_stop;
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("min_stop saved");
                                                                        delay_ms(500);
                                                                        CmdLCD(CLEAR_LCD);
                                                        }
                                                        else
                                                        {
                                                                        CmdLCD(GOTO_LINE2_POS0);
                                                                        StrLCD("Invalid");
                                                                        delay_ms(500);
                                                        }
                                }
                                }
}
//---------------------------------------------------------
// Function: EditMenu
// Displays the main edit menu and allows the user to select
// RTC editing, schedule editing, or exit.
//---------------------------------------------------------
void EditMenu()
{
                        u8 key;
//if(((IOPIN0>>SW_AL)&1)==0)
                        StrLCD("1.RTC_EDIT 3.E");
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("2.SCHEDULE_EDIT");

                        //n=ReadNUM();
                         while(Colscan()!=0)
                           key=keyscan();
                         delay_ms(300);
                        if(key=='1')
                        {

                                CmdLCD(CLEAR_LCD);
                                delay_ms(300);
                                RTC_EDIT();

                        }
                        if(key=='2')
                        {

																CmdLCD(CLEAR_LCD);
																delay_ms(300);
                                SCHEDULE_EDIT();

                        }
												if(key=='3')
												{
																return;
												}


}
/*unsigned int Iswithintime(void)
{
        if(START_TIME<STOP_TIME)
        {
                if(HOUR>=START_TIME && HOUR<STOP_TIME)
                {
                        return 1;
                }
        }
        else if(START_TIME>STOP_TIME)
        {
                if(HOUR>=START_TIME || HOUR<STOP_TIME)
                {
                        return 1;
                }
        }
        return 0;
}*/
//---------------------------------------------------------
// Function: Iswithintime
// Checks whether the current RTC time falls within the
// configured schedule. Converts the current, start, and end
// times into minutes to support normal and overnight ranges.
// Returns 1 when the current time is within the schedule;
// otherwise returns 0.
//---------------------------------------------------------
unsigned int Iswithintime(void)
{
    unsigned int currentMinutes;
    unsigned int startMinutes;
    unsigned int endMinutes;

    // Convert current RTC time into total minutes
    currentMinutes =(HOUR*60) + MIN;

    // Convert  start and end times into total minutes
    startMinutes = (Hr_START *60) +MIN_START;
    endMinutes = (Hr_STOP *60)+ MIN_STOP;

    // Normal schedule: start time is earlier than end time
    if(startMinutes <endMinutes)
    {
        if(currentMinutes>= startMinutes && currentMinutes <endMinutes)
            return 1;
    }

    // Overnight schedule: operating hours cross midnight
    else if(startMinutes >endMinutes)
    {
        if(currentMinutes >=startMinutes || currentMinutes< endMinutes)
            return 1;
    }

    return 0;
}





