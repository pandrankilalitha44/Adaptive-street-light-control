//---------------------------------------------------------
// Header Files
// Includes the delay function declarations and data type definitions.
//---------------------------------------------------------
#include "delay.h"
#include "types.h"
//---------------------------------------------------------
// Function: delay_us
// Generates an approximate delay in microseconds.
// Parameter: dlyus - Delay duration in microseconds.
// The input value is multiplied by 12 to obtain the loop count.
//---------------------------------------------------------
void delay_us(u32 dlyus)
{	
for(dlyus *= 12;dlyus>0;dlyus--);
}
//---------------------------------------------------------
// Function: delay_ms
// Generates an approximate delay in milliseconds.
// Parameter: dlyms - Delay duration in milliseconds.
// The input value is multiplied by 12000 to obtain the loop count.
//---------------------------------------------------------
  void delay_ms(u32 dlyms)
{
	for(dlyms *= 12000;dlyms>0;dlyms--);
}
//---------------------------------------------------------
// Function: delay_s
// Generates an approximate delay in seconds.
// Parameter: dlys - Delay duration in seconds.
// The input value is multiplied by 12000000 to obtain the loop count.
//---------------------------------------------------------
void delay_s(u32 dlys)
{
 	for(dlys *= 12000000;dlys>0;dlys--);
}
