//---------------------------------------------------------
// Header File Inclusions
//---------------------------------------------------------
// LPC21xx.h     = Provides LPC21xx microcontroller register definitions
// types.h       = Defines user-defined data types
// defines.h     = Contains common bit and port manipulation macros
// kpm_defines.h = Contains keypad pin and configuration definitions
// lcd.h         = Provides LCD interface function declarations
// lcd_defines.h = Contains LCD command and position definitions
// delay.h       = Provides delay function declarations
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
/*u8 kpmLUT[4][4]={
                  {0,1,2,3},
                  {4,5,6,7},
                  {8,9,10,11},
                  {12,13,14,15}
                 };*/
//---------------------------------------------------------
// Keypad Lookup Table
// Stores the character corresponding to each row and column
// position of the 4x4 matrix keypad.
//---------------------------------------------------------
u8 kpmLUT[][4]={
									{'7','8','9','/'},
									{'4','5','6','*'},
									{'1','2','3','-'},
									{'C','0','=','+'}
								};
//---------------------------------------------------------
// Function: InitKPM
// Configures the keypad row pins as output pins.
//---------------------------------------------------------
void InitKPM(void)
{
        WRITENIBBLE(IODIR1,Row0,0XF);
}
//---------------------------------------------------------
// Function: Colscan
// Checks whether any keypad column is active.
// Returns 0 when a key press is detected; otherwise returns 1.
//---------------------------------------------------------
u8 Colscan(void)
{
        u8 t;
        t=(READNIBBLE(IOPIN1,Col0)<15)?0:1;
        return t;
}
//---------------------------------------------------------
// Function: RowCheck
// Identifies the row in which the key is pressed by
// activating each row and checking the column status.
// Returns the detected row number.
//---------------------------------------------------------
u8 RowCheck(void)
{
        u8 r;
        for(r=0;r<4;r++)
        {
           WRITENIBBLE(IOPIN1,Row0,~(1<<r));
           if(!Colscan())
              break;
			  }
        WRITENIBBLE(IOPIN1,Row0,0);
        return r;
}
//---------------------------------------------------------
// Function: ColCheck
// Identifies the active column by checking each column pin.
// Returns the detected column number.
//---------------------------------------------------------
u8 ColCheck(void)
{
        u8 c;
        for(c=0;c<4;c++)
        {
                if(READBIT(IOPIN1,Col0 + c)==0)
                break;
        }
        return c;
}
//---------------------------------------------------------
// Function: keyscan
// Scans the keypad, identifies the pressed key using its
// row and column positions, and returns the key character.
//---------------------------------------------------------
u8 keyscan(void)
{
        u8 r,c,keyV;
        while(Colscan());
        r=RowCheck();
        c=ColCheck();
        keyV=kpmLUT[r][c];
        return keyV;
}
//---------------------------------------------------------
// Function: ReadTime
// Reads a maximum of two numeric digits from the keypad.
// Supports clearing with 'C', deleting the last digit with
// '*', and accepting the entered value with '='.
// num     = Pointer to store the entered number
// lastKey = Pointer to store the most recently pressed key
//---------------------------------------------------------
void ReadTime(u32 *num,u8 *lastKey){

    u32 cnt=0;
    u32 num2=0;

    while(1){
        *lastKey=keyscan();            // Store the most recently pressed key

        /* Accept numeric keys from 0 to 9, allowing a maximum of two digits */
        if(((*lastKey>='0' && *lastKey<='9'))&&(cnt<2)){
            num2=(num2 * 10)+(*lastKey-'0'); // Build the number by shifting previous digits left by one decimal place
            CmdLCD(GOTO_LINE1_POS0 + cnt++ + 14);
            CharLCD(*lastKey);         // Display the entered digit on LCD
            *num=num2;                 // Update the output with the entered number
            while(Colscan()==0);       // Wait until the pressed key is released

        }else{
            if(*lastKey=='C'){         //'C' clears the entered number
                CmdLCD(CLEAR_LCD);
                cnt=0;
                *num=0;
                num2=0;

            }else if(*lastKey=='*' && cnt>0){ //' * ' deletes the last entered digit
                num2=num2/10;          // Remove the last decimal digit
                --cnt;                 // Move the cursor position back
                CmdLCD(GOTO_LINE2_POS0 + cnt + 14);
                CharLCD(' ');          // Clear the previous digit from LCD
                *num=num2;             // Update the output after deletion

            }else if(*lastKey == '='){ // '=' acts as the enter key
                break;
            }

            while(Colscan()!=0);       // Wait until the pressed key is released
        }
    }
}

//---------------------------------------------------------
// Function: ReadYear
// Reads a maximum of four numeric digits from the keypad.
// Supports clearing with 'C', deleting the last digit with
// '*', and accepting the entered value with '='.
// num     = Pointer to store the entered year
// lastKey = Pointer to store the most recently pressed key
//---------------------------------------------------------
void ReadYear(u32 *num,u8 *lastKey){

    u32 cnt=0;
    u32 num2=0;

    while(1){
        *lastKey=keyscan();            // Store the most recently pressed key

        /* Accept numeric keys from 0 to 9, allowing a maximum of four digits */
        if(((*lastKey>='0' && *lastKey<='9'))&&(cnt<4)){
            num2=(num2 * 10)+(*lastKey-'0'); // Build the number by shifting previous digits left by one decimal place
            CmdLCD(GOTO_LINE1_POS0 + cnt++ + 10);
            CharLCD(*lastKey);         // Display the entered digit on LCD
            *num=num2;                 // Update the output with the entered number
            while(Colscan()==0);       // Wait until the pressed key is released

        }else{
            if(*lastKey=='C'){         //'C' clears the entered number
                CmdLCD(CLEAR_LCD);
                cnt=0;
                *num=0;
                num2=0;

            }else if(*lastKey=='*' && cnt>0){ //' * ' deletes the last entered digit
                num2=num2/10;          // Remove the last decimal digit
                --cnt;                 // Move the cursor position back
                CmdLCD(GOTO_LINE2_POS0 + cnt + 10);
                CharLCD(' ');          // Clear the previous digit from LCD
                *num=num2;             // Update the output after deletion

            }else if(*lastKey == '='){ // '=' acts as the enter key
                break;
            }

            while(Colscan()==0);       // Wait until the pressed key is released
        }
    }
}


