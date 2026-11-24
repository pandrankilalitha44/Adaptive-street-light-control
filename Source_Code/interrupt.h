/*
 * Header File: interrupt.h
 * -------------------------------------------------------
 * Contains function declarations for initializing and
 * handling External Interrupt 0 (EINT0).
 *
 * NOTE: The __irq keyword identifies the interrupt
 * service routine for the LPC21xx processor.
 */

//---------------------------------------------------------
// Header File Inclusion
//---------------------------------------------------------
#include <LPC21xx.h>

//---------------------------------------------------------
// Function Declarations
//---------------------------------------------------------

// Initializes External Interrupt 0 (EINT0).
void InitEINT0(void);

// Interrupt Service Routine (ISR) for External Interrupt 0.
// Executes when the EINT0 interrupt is triggered.
void eint0_isr(void)__irq;
