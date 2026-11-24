/*
 * Program: ADC Initialization and Reading
 * -------------------------------------------------------
 * This program initializes the ADC peripheral and reads
 * the digital value from the selected ADC channel.
 * The converted value is also calculated as an analog
 * voltage and stored in the supplied variable.
 *
 * NOTE: Refer to the LPC21xx user manual for ADC register
 * configuration and conversion details.
 */

//---------------------------------------------------------
// Header File Inclusion
//---------------------------------------------------------
#include "types.h"
#include <LPC21xx.h>
#include "adc_defines.h"
#include "delay.h"

//---------------------------------------------------------
// Function: Init_ADC
// Initializes the ADC peripheral and configures the
// required ADC input pins.
//---------------------------------------------------------
void Init_ADC(void)
{
        // Configure the pin function selection bits for ADC pins.
        PINSEL1&=~(0XFF<<((27-16)*2));
        // Select the ADC function for AIN0, AIN1, AIN2, and AIN3.
        PINSEL1|=AIN0_FUNC|AIN1_FUNC|AIN2_FUNC|AIN3_FUNC;
        // Power up the ADC and configure its clock divider.
        ADCR|=(1<<PDN_BIT)|(CLKDIV_VAL<<CLKDIV_BITS);
}

//---------------------------------------------------------
// Function: Read_ADC
// Performs an ADC conversion for the selected channel.
// chNo = ADC channel number to be converted.
// dVal = Pointer to store the 10-bit digital conversion result.
// eAR  = Pointer to store the corresponding analog voltage.
//---------------------------------------------------------
void Read_ADC(u8 chNo,u16 *dVal,f32 *eAR)
{
 // Clear the channel selection and conversion control bits.
ADCR&=0XFFFFFF00;
 // Select the requested ADC channel and start conversion.
ADCR|=(1<<ADC_CONV_START_BIT)|(1<<chNo);
 // Allow a short settling time after starting conversion.
delay_us(3);
 // Wait until the ADC conversion is completed.
while(((ADDR>>DONE_BIT)&1)==0);
 // Clear the conversion start bit after conversion is complete.
ADCR&=~(1<<ADC_CONV_START_BIT);
 // Extract the 10-bit digital result from the ADC data register.
*dVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
 // Convert the digital result into the corresponding voltage.
*eAR=*dVal*(3.3/1023);
}
