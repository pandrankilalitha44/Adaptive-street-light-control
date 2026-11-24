/*
 * Header File: KPM (Keypad Module)
 * --------------------------------
 * Contains function declarations for keypad scanning,
 * key checking, and numeric/time input routines.
 *
 * Include this header wherever these functions are used.
 */

/* Provides the u8 and u32 data types used in the declarations. */
#include "types.h"

/*---------------------------------------------
 * Keypad Initialization and Scanning Functions
 *---------------------------------------------*/

// Initializes the keypad interface and its required configuration.
void InitKPM(void);

// Scans the keypad columns and returns the scan result.
u8 Colscan(void);

// Scans the keypad rows and returns the scan result.
u8 Rowscan(void);

/*---------------------------------------------
 * Keypad Row and Column Checking Functions
 *---------------------------------------------*/

// Checks the keypad column state and returns the result.
u8 Colcheck(void);

// Checks the keypad row state and returns the result.
u8 Rowcheck(void);

/*---------------------------------------------
 * Key and Numeric Input Functions
 *---------------------------------------------*/

// Reads and returns a numeric value.
u32 ReadNUM(void);

// Reads a numeric value using the supplied pointers.
void ReadNum2(u32 *,u8 *);

// Scans the keypad and returns the detected key value.
u8 keyscan(void);

/*---------------------------------------------
 * Time, Number, and Year Input Functions
 *---------------------------------------------*/

// Reads time-related input and stores the result through pointers.
void ReadTime(u32 *,u8 *);

// Reads numeric input and stores the result through pointers.
void ReadNums(u32 *,u8 *);

// Reads year input and stores the result through pointers.
void ReadYear(u32 *,u8 *);
