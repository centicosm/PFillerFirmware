/* 
 * File:   PLCD.h
 * Author: pulam
 *
 *     Header for the PLCD library
 */

#ifndef PLCD_H
#define	PLCD_H

//#include <xc.h>
//#include <stdbool.h>
#include "PLCD_Settings.h"


// ---------------   LCD State -------------------------------------
#ifdef LCD_MAINTAIN_STATE

#define LCD_SETTING_DDRAM_MODE       0b00000001
#define LCD_SETTING_DISPLAY_SHIFT    0b00000010
#define LCD_SETTING_CURSOR_INC       0b00000100
#define LCD_SETTING_SHOW_CURSOR      0b00001000
#define LCD_SETTING_CURSOR_BLINK     0b00010000
#define LCD_SETTING_DISPLAY_ON       0b00100000
#define LCD_SETTING_INITIALIZED      0b10000000

typedef enum LCD_CURSOR_DIRECTION_t {
    LCD_CURSOR_RIGHT,
    LCD_CURSOR_LEFT
} LCD_CURSOR_DIRECTION;

// holds various lcd display settings such as cursor state and behavior
extern unsigned char _LCD_Settings;

 /* TODO Need to handle cases where shifting is on as we could not be off the display
          Also need to examine details of the shifting behavior */
// stores the character that the cursor is on
//  0    1     2   ...  x
// x+1  x+2   x+3  ...  2x
extern unsigned char _LCD_Pos_X;
extern unsigned char _LCD_Pos_Y;

// turns on or off display shifting
void LCD_SetDisplayShift(bool shift);

// sets the direction the cursor should move
void LCD_SetCursorMovement(LCD_CURSOR_DIRECTION dir);

// turns the cursor on or off
void LCD_ShowCursor(bool cur);

// turns the cursor blinking on or off
void LCD_BlinkCursor(bool cur);


#endif



// LCD Settings

// display appearance
#define LCD_DISPLAY_ON          0b00000100
#define LCD_DISPLAY_OFF         0b00000000
#define LCD_CURSOR_ON           0b00000010
#define LCD_CURSOR_OFF          0b00000000
#define LCD_CURSOR_BLINK_ON     0b00000001
#define LCD_CURSOR_BLINK_OFF    0b00000000

#define LCD_CMD_FUNCTION_SET    0b00100000
#define LCD_FUNCTION_8_BIT      0b00010000
#define LCD_FUNCTION_4_BIT      0b00000000
#define LCD_FUNCTION_2_LINES    0b00001000
#define LCD_FUNCTION_1_LINE     0b00000000
#define LCD_FUNCTION_FONT_5x8   0b00000000
#define LCD_FUNCTION_FONT_5x10  0b00000100

#define LCD_CMD_SET_ENTRY_MODE  0b00000100
#define LCD_ENTRY_INCREMENT     0b00000010
#define LCD_ENTRY_DECREMENT     0b00000000
#define LCD_ENTRY_SHIFT         0b00000001

#define LCD_CMD_DSIPLAY_CNTL          0b00001000
#define LCD_DISPLAY_OFF               0b00000000
#define LCD_DISPLAY_CURSOR_ON         0b00000010
#define LCD_DISPLAY_CURSOR_OFF        0b00000000
#define LCD_DISPLAY_CURSOR_BLINK_ON   0b00000001
#define LCD_DISPLAY_CURSOR_BLINK_OFF  0b00000000

#define LCD_CMD_CLEAR                0b00000001
#define LCD_CMD_RETURN_HOME          0b00000010
#define LCD_CMD_SET_DDRAM_ADDR       0b10000000


#define LCD_CMD_MOVE_DISPLAY         0b00010000
#define LCD_MOVE_CURSOR              0b00000000
#define LCD_SHIFT_DISPLAY            0b00001000
#define LCD_MOVE_RIGHT               0b00000100
#define LCD_MOVE_LEFT                0b00000000

#define LCD_CMD_SET_CGRAM_ADDR       0b01000000


#define LCD_DisplayControl(x)        LCD_WriteCommand(LCD_CMD_DSIPLAY_CNTL | x);
#define LCD_DisplayOff()             LCD_WriteCommand(LCD_CMD_DISPLAY_CNTL | LCD_DISPLAY_OFF)
#define LCD_DisplayOn(x)             LCD_WriteCommand(LCD_CMD_DISPLAY_CNTL | LCD_DISPLAY_ON | x)
#define LCD_CursorCntl(x)            LCD_WriteCommand(LCD_CMD_DISPLAY_CNTL | LCD_DISPLAY_ON | x)



// -----------------------------------------------------------------
//extern unsigned char _LCD_YPos;



// Initialize the LCD with the parameters passed
void LCD_Initialize(unsigned char initConfig);

// Write a command to the LCD
void LCD_WriteCommand(unsigned char cmd);

// Clear the LCD screen and return to home
void LCD_ClearScreen(void);

// Return to the home position (0,0)
void LCD_ReturnHome(void);

// Go to the specified location on the screen (invalid locations are not looked for)
void LCD_GotoXY(unsigned char x, unsigned char y);

// Set the cursor/screen behavior when writing or reading to the LCD
void LCD_SetEntryMode(unsigned char mode);


// set the address and read mode to CG Ram
void LCD_SetCGRAMAddr(unsigned char addr);


// Write a character to the lcd
void LCD_WriteChar(unsigned char ch);

// write a null terminated string to the lcd
void LCD_WriteStringRAM(const char *str);


void LCD_WriteStringROM(rom const char *str);


// write a string of length len to the lcd
void LCD_WriteStringLenRAM(const char *str, unsigned char len);

// write a string of length len to the lcd
void LCD_WriteStringLenROM(rom const char *str, unsigned char len);

// Checks to see if the LCD is currently executing an internal operation
bool LCD_IsBusy(void);

// Send a byte of data to the lcd
void LCD_SendData(unsigned char data);


void LCD_WaitForNotBusy(void);


void LCD_SetCGRAMCharRAM(unsigned char index, const char *bytes);

void LCD_SetCGRAMCharROM(unsigned char index, rom const char *bytes);


#endif	/* PLCD_H */
