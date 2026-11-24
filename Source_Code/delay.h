/*
 * Header File: delay.h
 * -------------------------------------------------------
 * Contains function declarations for generating delays
 * in microseconds, milliseconds, and seconds.
 *
 * NOTE: Include this header file wherever the delay
 * functions are required.
 */

//---------------------------------------------------------
// Header File Inclusion
//---------------------------------------------------------
#include "types.h"

//---------------------------------------------------------
// Function Declarations
//---------------------------------------------------------

// Generates a delay for the specified duration in microseconds.
// dlyUS = Delay duration in microseconds.
void delay_us(u32 dlyUS);

// Generates a delay for the specified duration in milliseconds.
// dlyMS = Delay duration in milliseconds.
void delay_ms(u32 dlyMS);

// Generates a delay for the specified duration in seconds.
// dlyS = Delay duration in seconds.
void delay_s(u32 dlyS);
