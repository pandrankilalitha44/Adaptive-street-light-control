/*
 * Program: LDR Sensor Reading and Light Intensity Calculation
 * -------------------------------------------------------
 * Reads the LDR voltage through ADC, calculates the LDR
 * resistance, and estimates the surrounding light intensity
 * in lux.
 */

//---------------------------------------------------------
// Header File Inclusions
//---------------------------------------------------------
#include <math.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"

//---------------------------------------------------------
// Global Variables
//---------------------------------------------------------
// dval = Stores the digital ADC value.
// adc  = Stores the ADC reading returned to the caller.
u16 dval,adc;f32 eAR;
f32 volt,Rldr,lux;

//---------------------------------------------------------
// Function: Read_LDR
// Reads the LDR sensor value and calculates voltage,
// resistance, and light intensity.
// adc  = Pointer to store the digital ADC value.
// volt = Pointer to store the measured voltage.
// Rldr = Pointer to store the calculated LDR resistance.
// lux  = Pointer to store the estimated light intensity.
//---------------------------------------------------------
void Read_LDR(u16 *adc,f32 *volt,f32 *Rldr,f32 *lux)
{
        //u16 dval;f32 eAR;
        //f32 Rldr;
        // Initialize the ADC only once when the function is called for the first time.
        static u32 flag=0;
        if(flag==0)
        {
                Init_ADC();
                flag=1;
        }
        // Read the ADC channel 0 value and convert it into the equivalent voltage.
        Read_ADC(0,&dval,&eAR);
			  //u32LCD(dval);
				//u32LCD(eAR);
        // Copy the ADC digital value and calculated voltage to the output variables.
				*adc=dval;
			  *volt=eAR;
        // Calculate the LDR resistance using the voltage divider formula.
        *Rldr=(10000.0f*(*volt))/(3.3f-(*volt));
        // Calculate the light intensity only when the calculated resistance is positive.
				if(*Rldr>0)
				{
					*lux=10.0f*pow((12000.0f/(*Rldr)),(1.0f/0.7f));
				}
				else
				{
                    // Assign a minimum lux value when the resistance is zero or negative.
					*lux=1;
				}
}






















	
	
	