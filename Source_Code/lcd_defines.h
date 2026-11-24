//HD44780 commands
// Clear the LCD display.
#define CLEAR_LCD 0X01
// Return the LCD cursor to the home position.
#define RET_CUR_HOME 0X02
// Set cursor movement direction to the right.
#define SHIFT_CUR_RIGHT 0X06
// Set cursor movement direction to the left.
#define SHIFT_CUR_LEFT 0X07
// Turn the LCD display off.
#define DSP_OFF 0X08
// Turn the LCD display on and keep the cursor off.
#define DSP_ON_CUR_OFF 0X0C
// Turn the LCD display on and show the cursor.
#define DSP_ON_CUR_ON 0X0E
// Turn the LCD display on with a blinking cursor.
#define DSP_ON_CUR_BLK 0X0F
// Shift the displayed content one position to the left.
#define SHIFT_DSP_LEFT 0X10
// Shift the displayed content one position to the right.
#define SHIFT_DSP_RIGHT 0X14
// Configure the LCD for 8-bit mode with one line.
#define MODE_8BIT_1LINE 0X30
// Configure the LCD for 4-bit mode with one line.
#define MODE_4BIT_1LINE 0X20
// Configure the LCD for 8-bit mode with two lines.
#define MODE_8BIT_2LINE 0X38
// Configure the LCD for 4-bit mode with two lines.
#define MODE_4BIT_2LINE 0X28
// Set the LCD cursor to line 1, position 0.
#define GOTO_LINE1_POS0 0X80
// Set the LCD cursor to line 2, position 0.
#define GOTO_LINE2_POS0 0XC0
// Set the LCD cursor to line 3, position 0.
#define GOTO_LINE3_POS0 0X94
// Set the LCD cursor to line 4, position 0.
#define GOTO_LINE4_POS0 0XD4
// LCD data port/bit position.
#define LCD_DATA 16
// LCD Register Select control bit.
#define LCD_RS 8
// LCD Read/Write control bit.
#define LCD_RW 9
// LCD Enable control bit.
#define LCD_EN 10
// Starting address for the LCD CGRAM.
#define GOTO_CGRAM_START 0X40
