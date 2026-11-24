//---------------------------------------------------------
// Header File Inclusions
//---------------------------------------------------------
// types.h       = Defines user-defined data types
// LPC21xx.h     = Provides LPC21xx microcontroller register definitions
// defines.h     = Contains common bit and port manipulation macros
// lcd_defines.h = Contains LCD pin definitions and command values
// delay.h       = Provides delay function declarations
// lcd.h         = Provides LCD interface function declarations
#include "types.h"
#include <LPC21xx.h>
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
#include "lcd.h"
/*void WriteLCD(u8 dat)
{
   WRITEBYTE(IOPIN0,LCD_DATA,dat);
   IOCLR0=1<<LCD_RW;
   IOSET0=1<<LCD_EN;
   delay_us(1);
   IOCLR0=1<<LCD_EN;
   delay_ms(2);
}*/
//---------------------------------------------------------
// Function: WriteLCD
// Sends an 8-bit data or command value to the LCD through
// the data pins and generates the required enable pulse.
// dat = 8-bit value to be sent to the LCD
//---------------------------------------------------------
void WriteLCD(u8 dat)
{
    // Clear LCD data pins P0.8 to P0.15
    IOCLR0 = (0xFF << LCD_DATA);
    // Set the required data bits
    IOSET0 = ((u32)dat << LCD_DATA);
    // Select LCD write operation
    IOCLR0 = 1<< LCD_RW;
    // Generate enable pulse
    IOSET0 = 1<<LCD_EN;
    delay_us(1);
    IOCLR0 =1<<LCD_EN;
    delay_ms(2);
}
//---------------------------------------------------------
// Function: CmdLCD
// Sends a command instruction to the LCD.
// cmd = Command value to be sent
//---------------------------------------------------------
void CmdLCD(u8 cmd)
{
   IOCLR0=1<<LCD_RS;
   WriteLCD(cmd);
}
//---------------------------------------------------------
// Function: CharLCD
// Sends an ASCII character to the LCD for display.
// asciival = ASCII value of the character to be displayed
//---------------------------------------------------------
void CharLCD(u8 asciival)
{
   IOSET0=1<<LCD_RS;
   WriteLCD(asciival);
}
//---------------------------------------------------------
// Function: InitLCD
// Configures the LCD interface pins and initializes the LCD
// in 8-bit, 2-line mode with the display and cursor settings.
//---------------------------------------------------------
void InitLCD(void)
{
IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
delay_ms(15);
CmdLCD(0x30);
delay_ms(4);
delay_us(100);
CmdLCD(0x30);
delay_us(100);
CmdLCD(0x30);
CmdLCD(MODE_8BIT_2LINE);
CmdLCD(DSP_ON_CUR_BLK);
CmdLCD(CLEAR_LCD);
CmdLCD(SHIFT_CUR_RIGHT);
}
//---------------------------------------------------------
// Function: StrLCD
// Displays a null-terminated string on the LCD.
// s = Pointer to the string to be displayed
//---------------------------------------------------------
void StrLCD(s8 *s)
{
  while(*s)
  CharLCD(*s++);
}
//---------------------------------------------------------
// Function: u32LCD
// Converts an unsigned integer into decimal digits and
// displays the digits on the LCD.
// n = Unsigned integer value to be displayed
//---------------------------------------------------------
void u32LCD(u32 n)
{
   u8 a[10];
   s32 i=0;
   if(n==0)
   {
   CharLCD('0');
   }
   else
   {
  while(n>0)
  {
   a[i]=(n%10)+48;
   n/=10;
   i++;
  }
   for(--i;i>=0;i--)
  {
   CharLCD(a[i]);
  }
  }
}
//---------------------------------------------------------
// Function: s32LCD
// Displays a signed integer on the LCD, including its
// negative sign when the supplied value is negative.
// sn = Signed integer value to be displayed
//---------------------------------------------------------
void s32LCD(s32 sn)
{
if(sn<0)
{
CharLCD('-');
sn=-sn;
}
u32LCD(sn);
}
//---------------------------------------------------------
// Function: F32LCD
// Displays a floating-point value on the LCD with the
// specified number of digits after the decimal point.
// fN  = Floating-point value to be displayed
// nDP = Number of decimal places to display
//---------------------------------------------------------
void F32LCD(f32 fN,u8 nDP)
{
u32 n,i;
if(fN<0.0)
{
CharLCD('-');
fN=-fN;
}
n=fN;
u32LCD(n);
CharLCD('.');
for(i=0;i<nDP;i++)
{
fN=(fN-n)*10;
n=fN;
CharLCD(n+48);
}
}
//---------------------------------------------------------
// Function: BuildCGRAM
// Writes custom character pattern bytes into the LCD's
// Character Generator RAM (CGRAM).
// p      = Pointer to the custom character pattern data
// nBytes = Number of pattern bytes to write
//---------------------------------------------------------
void BuildCGRAM(u8 *p,u8 nBytes)
{
u32 i;
CmdLCD(GOTO_CGRAM_START);
IOSET0=1<<LCD_RS;
IOCLR0=1<<LCD_RW;
for(i=0;i<nBytes;i++)
{
WriteLCD(p[i]);
}
CmdLCD(GOTO_LINE1_POS0);
}

