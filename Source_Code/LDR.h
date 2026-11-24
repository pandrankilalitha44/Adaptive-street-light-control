// LDR (Light Dependent Resistor) interface header file
// Provides the function declaration used to read/process LDR sensor data.

// Include the project's common type definitions.
#include "types.h"
// Function declaration for reading LDR data.
// Parameters:
//   u16 *  - pointer to the LDR-related input/data source
//   f32 *  - pointer to the first floating-point output value
//   f32 *  - pointer to the second floating-point output value
//   f32 *  - pointer to the third floating-point output value
// Returns:
//   u32   - status/result value returned by the LDR read operation.
u32 Read_LDR(u16 *,f32 *,f32 *,f32 *);
