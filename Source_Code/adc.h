// ADC (Analog-to-Digital Converter) header file
// Contains the declarations for initializing and reading the ADC.

// Include common project type definitions.
#include "types.h"
// Initializes the ADC peripheral.
void Init_ADC(void);
// Reads the ADC value from the specified channel.
// chNo: ADC channel number.
// dVal: pointer used to return the digital ADC value.
// eAR: pointer used to return the corresponding electrical/analog result.
void Read_ADC(u8 chNo,u16 *dVal,f32 *eAR);
