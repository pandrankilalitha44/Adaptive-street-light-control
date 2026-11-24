/*
    File: lcd.h
    -------------------------------------------------------
    This header file contains function declarations for LCD
    operations used by the LPC2148 project.
    These functions are used to send commands, display data,
    strings, and numeric values on the LCD.
*/

#include "types.h"   // Includes user-defined data types such as u8, s8, u32, s32, and f32
// Writes a data byte to the LCD.
void WriteLCD(u8 dat);
// Sends a command instruction to the LCD.
void CmdLCD(u8 cmd);
// Displays a single ASCII character on the LCD.
void CharLCD(u8 asciival);
// Initializes the LCD for display operation.
void InitLCD(void);
// Displays a string of characters on the LCD.
void StrLCD(s8 *);
// Displays an unsigned 32-bit integer on the LCD.
void u32LCD(u32);
// Displays a signed 32-bit integer on the LCD.
void s32LCD(s32);
// Displays a floating-point value with the specified number of decimal places.
void F32LCD(f32,u8);
// Creates a custom character in the LCD Character Generator RAM (CGRAM).
void BuildCGRAM(u8*,u8);
