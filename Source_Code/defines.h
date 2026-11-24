/*
 * Header File: defines.h
 * -------------------------------------------------------
 * Contains commonly used macros for bit, nibble, and byte
 * operations on register or variable values.
 *
 * NOTE: These macros provide reusable bitwise operations
 * for accessing and modifying selected portions of a WORD.
 */

//---------------------------------------------------------
// Macro: WRITEBYTE
// Replaces 8 bits in a WORD starting from STARTBIT.
// WORD     = Register or variable to be modified
// STARTBIT = Starting bit position of the byte
// BYTE     = 8-bit value to be written
// Example: WRITEBYTE(IODIR0, 8, 0xFF) sets bits 8 to 15.
//---------------------------------------------------------
#define WRITEBYTE(WORD,STARTBIT,BYTE)\
            WORD=((WORD&~(0XFF<<STARTBIT))|\
                        (BYTE<<STARTBIT))
// Reads and returns the value of the bit at the specified position.
// WORD = Register or variable to be read
// BIT  = Bit position to be checked
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
// Sets the specified bit of a WORD to 1 without changing other bits.
// WORD = Register or variable to be modified
// BIT  = Bit position to be set
#define SETBIT(WORD,BIT)   (WORD|=1<<BIT)
//---------------------------------------------------------
// Macro: WRITENIBBLE
// Replaces 4 bits in a WORD starting from STARTBIT.
// WORD     = Register or variable to be modified
// STARTBIT = Starting bit position of the nibble
// BYTE     = 4-bit value to be written
// Example: WRITENIBBLE(PORT, 4, 0xF) sets bits 4 to 7.
//---------------------------------------------------------
#define WRITENIBBLE(WORD,STARTBIT,BYTE)\
            WORD=((WORD&~(0XF<<STARTBIT))|\
                        (BYTE<<STARTBIT))
// Reads and returns the 4-bit nibble starting from BIT.
// WORD = Register or variable to be read
// BIT  = Starting bit position of the nibble
#define READNIBBLE(WORD,BIT) ((WORD>>BIT)&0XF)
