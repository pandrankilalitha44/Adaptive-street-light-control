/*
 * File Name : rtc.h
 * Description:
 *   Contains function declarations for RTC initialization, time and date
 *   handling, day information, time-window checking, and RTC/schedule
 *   editing operations used by the application.
 *
 * Note:
 *   This header provides function prototypes. The corresponding function
 *   definitions are implemented in the source file.
 */

// LPC2148 device register definitions and device-specific declarations.
#include <LPC21xx.h>
// Common project data types, including the u32 type used below.
#include "types.h"

//---------------------------------------------------------
// RTC Initialization
//---------------------------------------------------------
// Initializes the Real-Time Clock peripheral.
void RTC_Init(void);

//---------------------------------------------------------
// RTC Time Information
//---------------------------------------------------------
// Reads the current RTC time into the supplied variables.
// The pointer parameters allow the function to return values
// to the calling function.
void GetRTCTimeInfo(u32 *,u32 *,u32 *);
// Displays the supplied hour, minute, and second values.
void DisplayRTCTime(u32,u32,u32);

//---------------------------------------------------------
// RTC Date Information
//---------------------------------------------------------
// Reads the current RTC date into the supplied variables.
void GetRTCDateInfo(u32 *,u32 *,u32 *);
// Displays the supplied date, month, and year values.
void DisplayRTCDate(u32,u32,u32);

//---------------------------------------------------------
// RTC Time and Date Update
//---------------------------------------------------------
// Sets the RTC time using the supplied hour, minute, and second.
// Sets the RTC date using the supplied date, month, and year.
void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);

//---------------------------------------------------------
// RTC Day Information
//---------------------------------------------------------
// Reads the current day value through the pointer parameter.
// Displays the supplied day value.
// Updates the RTC day using the supplied value.
void GetRTCDay(u32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);

//---------------------------------------------------------
// Time-Window and Menu Editing Functions
//---------------------------------------------------------
// Returns a status indicating whether the current time is
// within the configured time window.
// Handles RTC time/date editing.
// Handles street-light schedule editing.
// Provides the edit-menu functionality.
unsigned int Iswithintime(void);
void RTC_EDIT(void);
void SCHEDULE_EDIT(void);
void EditMenu(void);


