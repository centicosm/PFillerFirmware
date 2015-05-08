//#include <pic18.h>
#include "PFiller_Globals.h"
#include "PLCD_Settings.h"

// http://www.romux.com/tutorials/pic-tutorial/lcd-display


#ifdef LCD_MAINTAIN_STATE
    unsigned char _LCD_Settings = 0;
    unsigned char _LCD_Pos_X = 0;
    unsigned char _LCD_Pos_Y = 0;
#endif



// macro to pulse the enable line
void LCD_Enable(void)  {
    LCD_E = 1;
    _asm
            NOP
            NOP
            NOP
            NOP
    _endasm
    LCD_E = 0;
}




void LCD_Initialize(unsigned char initConfig) {

        // The data bits must be either a 8-bit port or the upper or
        // lower 4-bits of a port. These pins are made into inputs
#ifdef LCD_DATA_8BIT                             // 8-bit mode, use whole port
    LCD_DATAPORT = 0;
    LCD_DATAPORT_TRIS = 0x00;
    initConfig |= 0b00010000;           // make sure the init bit field matches that defines in the header

#else                                   // 4-bit mode
#ifdef  LCD_4_BIT_UPPER_NIBBLE
        // Upper 4-bits of the port
        LCD_DATAPORT &= 0x0f;
        LCD_DATAPORT_TRIS &= 0x0F;
        initConfig &= 0b11101111;           // make sure the init bit field matches that defines in the header

#else                                   // Lower 4-bits of the port
        LCD_DATAPORT &= 0xF0;
        LCD_DATAPORT_TRIS &= 0xF0;
        initConfig &= 0b11101111;           // make sure the init bit field matches that defines in the header
#endif
#endif
        LCD_RW_TRIS = OUTPUT_TRIS;         // All control signals made outputs and initialized low
        LCD_RS_TRIS = OUTPUT_TRIS;
        LCD_E_TRIS = OUTPUT_TRIS;
        LCD_RW = 0;                     // R/W pin made low
        LCD_RS = 0;                     // Register select pin made low
        LCD_E = 0;                      // Clock pin made low

        // Delay for 50ms to allow for LCD Power on reset
        Delay_10x_ms(5);

        // software reset
        LCD_WriteCommand(0b00110000);    // set to 4-bit interface
        Delay_ms(5);

        LCD_WriteCommand(0b00110000);
        Delay_5x_us(100);

        LCD_WriteCommand(0b00110000);

        LCD_WaitForNotBusy();                                     // LCD is now minimally set up so we can start checking the busy flag

#ifdef LCD_INTERFACE_8_BIT
        LCD_WriteCommand(LCD_CMD_FUNCTION_SET | LCD_FUNCTION_8_BIT | initConfig);   // Set the font, number of lines, and interface size to the user selected values
#else
        LCD_WriteCommand(LCD_CMD_FUNCTION_SET | LCD_FUNCTION_4_BIT | initConfig);   // Set the font, number of lines, and interface size to the user selected values
#endif

        // default cursor and display properties to off
        LCD_WaitForNotBusy();
        LCD_WriteCommand(LCD_CMD_DSIPLAY_CNTL | LCD_DISPLAY_OFF | LCD_DISPLAY_CURSOR_OFF | LCD_DISPLAY_CURSOR_BLINK_OFF);

        LCD_WaitForNotBusy();
        LCD_ClearScreen();

        LCD_WaitForNotBusy();
        LCD_WriteCommand(LCD_CMD_SET_ENTRY_MODE | LCD_ENTRY_INCREMENT);   // initialize the display with the desired appearance


#ifdef LCD_MAINTAIN_STATE
    _LCD_Pos_X = 0;
    _LCD_Pos_Y = 0;
    _LCD_Settings = LCD_SETTING_DDRAM_MODE | LCD_SETTING_CURSOR_INC | LCD_SETTING_INITIALIZED;
#endif

}



// write a command to the LCD
void LCD_WriteCommand(unsigned char cmd) {

#ifdef LCD_INTERFACE_8_BIT
    LCD_DATAPORT_TRIS = OUTPUT_TRIS;
    LCD_DATAPORT = cmd;
#else

    // 4-bit mode
    #ifdef LCD_4_BIT_UPPER_NIBBLE
        LCD_DATAPORT_TRIS &= 0x0F;
        LCD_DATAPORT &= 0x0F;
        LCD_DATAPORT |= (cmd & 0xF0);
    #else
        LCD_DATAPORT_TRIS &= 0xF0;
        LCD_DATAPORT &= 0xF0;
        LCD_DATAPORT |= ((cmd & 0xF0) >> 4);
    #endif
#endif


    LCD_RS = 0;     // we are sending a command
    LCD_RW = 0;     // we will be writing

    LCD_Enable();    // Actually send the command

// if we are in 4 bit mode send the second nibble
#ifndef LCD_INTERFACE_8_BIT
    #ifdef LCD_4_BIT_UPPER_NIBBLE
        LCD_DATAPORT &= 0x0F;
        LCD_DATAPORT |= ((cmd & 0x0F) << 4);
    #else
        LCD_DATAPORT &= 0xF0;
        LCD_DATAPORT |= (cmd & 0x0F);
    #endif

    LCD_Enable();
#endif

}

// clear the screen
void LCD_ClearScreen(void) {

    LCD_WaitForNotBusy();

    LCD_WriteCommand(LCD_CMD_CLEAR);

#ifdef LCD_MAINTAIN_STATE
    _LCD_Pos_X = 0;
    _LCD_Pos_X = 0;
    /* TODO - Determine if this command results in pointing at DDRam */
    _LCD_Settings |= LCD_SETTING_DDRAM_MODE;
#endif
}


// return to position 0,0  (without clearing the screen)
void LCD_ReturnHome() {

    LCD_WaitForNotBusy();
    LCD_WriteCommand(LCD_CMD_RETURN_HOME);

#ifdef LCD_MAINTAIN_STATE
    _LCD_Pos_X = 0;
    _LCD_Pos_Y = 0;

    /* TODO - Determine if this command results in pointung at DDRam */
    _LCD_Settings |= LCD_SETTING_DDRAM_MODE;
#endif
}


void LCD_GotoXY(unsigned char x, unsigned char y) {
    unsigned char ddramOffset = x;

    // we will not allow goto's to undefined locations
    if (x  >= LCD_CHAR_PER_LINE) return;
#ifdef LCD_1_LINE
    if (y  > 0) return;
#endif
#ifdef LCD_2_LINE
    if (y  > 1) return;
#endif
#ifdef LCD_4_LINE
    if (y  > 3) return;
#endif



#ifdef  LCD_2_LINE
    if (y == 1)  {
        ddramOffset += 0x40;
    }
#endif
    
#ifdef LCD_4_LINE

    if (y == 1) {
        ddramOffset += 0x40;
    }
    else if (y == 2) {
        ddramOffset += 0x14;
    }
    else if (y == 3) {
        ddramOffset += 0x54;
    }
#endif

#ifdef LCD_MAINTAIN_STATE
       _LCD_Pos_X = x;
       _LCD_Pos_Y = y;
       _LCD_Settings |= LCD_SETTING_DDRAM_MODE;
#endif

    LCD_WaitForNotBusy();
    LCD_WriteCommand(LCD_CMD_SET_DDRAM_ADDR | ddramOffset);
}



// write a command to the lcd
void LCD_WriteChar(unsigned char ch) {

    // if we are not pointing at ddram, start pointing at the location in ddram we were last pointing at
#ifdef LCD_MAINTAIN_STATE
    if (!(_LCD_Settings & LCD_SETTING_DDRAM_MODE)) {
        LCD_GotoXY(_LCD_Pos_X, _LCD_Pos_Y);
    }
#endif

    // send the character to DDRAM
    LCD_SendData(ch);


#ifdef LCD_MAINTAIN_STATE

    // we only track positions when writing the the screen (ddram)
    if (_LCD_Settings & LCD_SETTING_DDRAM_MODE) {

        _LCD_Pos_X++;
        if (_LCD_Pos_X == LCD_CHAR_PER_LINE) {
            _LCD_Pos_X = 0;

#ifdef LCD_2_LINE
            _LCD_Pos_Y++;
            if (_LCD_Pos_Y == 2) _LCD_Pos_Y = 0;
#endif

#ifdef LCD_4_LINE
            _LCD_Pos_Y++;
            if (_LCD_Pos_Y == 4) _LCD_Pos_Y = 0;
#endif
            LCD_GotoXY(0, 0);
        }
    }
#endif
}


void LCD_SendData(unsigned char data) {

    // wait before writing the next character
    LCD_WaitForNotBusy();

#ifdef LCD_INTERFACE_8_BIT
    LCD_DATAPORT_TRIS = OUTPUT_TRIS;
    LCD_DATAPORT = data;
#else

    // 4-bit mode
    #ifdef LCD_4_BIT_UPPER_NIBBLE
        LCD_DATAPORT_TRIS &= 0x0F;
        LCD_DATAPORT &= 0x0F;
        LCD_DATAPORT |= (data & 0xF0);
    #else
        LCD_DATAPORT_TRIS &= 0xF0;
        LCD_DATAPORT &= 0xF0;
        LCD_DATAPORT |= ((data & 0xF0) >> 4);
    #endif
#endif

    LCD_RS = 1;     // we are sending a command
    LCD_RW = 0;     // we will be writing

    LCD_Enable();    // Actually send the command

// if we are in 4 bit mode send the second nibble
#ifndef LCD_INTERFACE_8_BIT
    #ifdef LCD_4_BIT_UPPER_NIBBLE
        LCD_DATAPORT &= 0x0F;
        LCD_DATAPORT |= ((data & 0x0F) << 4);
    #else
        LCD_DATAPORT |= 0xF0;
        LCD_DATAPORT |= (data & 0x0F);
    #endif

    LCD_Enable();
#endif

}


// write a string to the lcd.  The string can be null terminated or of a specified length
void LCD_WriteStringLenRAM(const char *str, unsigned char len) {
    unsigned char i;
    for (i = 0; i < len; i++)  {
        LCD_WriteChar(str[i]);
    }
}

// write a string to the lcd.  The string can be null terminated or of a specified length
void LCD_WriteStringLenROM(rom const char *str, unsigned char len) {
    unsigned char i;
    for (i = 0; i < len; i++)  {
        LCD_WriteChar(str[i]);
    }
}

// write a null terminated string to the lcd
void LCD_WriteStringRAM(const char *str) {
    unsigned char i = 0;
    while (str[i] != 0) {
        LCD_WriteChar(str[i]);
        i++;
    };
}


// write a null terminated string to the lcd
void LCD_WriteStringROM(rom const char *str) {
    unsigned char i = 0;
    while (str[i] != 0) {
        LCD_WriteChar(str[i]);
        i++;
    };
}




// spin until the LCD says it is no longer busy
void LCD_WaitForNotBusy(void) {

// if we are maintaining LCD State, if the LCD is not initialized, lets delay instead of  checking the busy flag that should not be working
#ifdef LCD_MAINTAIN_STATE
    if (!(_LCD_Settings & LCD_SETTING_INITIALIZED)) {

        // 2 ms should be longer than any delay necessary following a command
        Delay_ms(2);
        return;
    }
#endif

    // send the monitor busy signal and wait for busy to go low
    //   DANGER:  We could be stuck here forever if LCD_BUSY never goes low
    LCD_BUSY_TRIS = INPUT_TRIS;
    LCD_RS = false;
    LCD_RW = true;
    LCD_E = true;
    while (LCD_BUSY);
    LCD_E = false;
    LCD_BUSY_TRIS = OUTPUT_TRIS;
    return;
}



// set the address and read mode to CG Ram
void LCD_SetCGRAMAddr(unsigned char addr) {

    LCD_WaitForNotBusy();
    addr &= 0b00111111;             // make sure the address is within bounds
    LCD_WriteCommand(LCD_CMD_SET_CGRAM_ADDR | addr);

#ifdef LCD_MAINTAIN_STATE
    _LCD_Settings &= ~LCD_SETTING_DDRAM_MODE;
#endif
}


// Enter a custom character into cgram
void LCD_SetCGRAMCharRAM(unsigned char index, const char *bytes) {
    unsigned char i;

//  If we are not already in cgram mode, switch to it before adding the new characters
#ifdef LCD_MAINTAIN_STATE
    unsigned char changeBack = 0;
    if (!(_LCD_Settings & LCD_SETTING_DDRAM_MODE)) {
   //     LCD_SetCGRAMAddr(index);
        changeBack = 1;
    }
#endif

    LCD_SetCGRAMAddr(index * 8);

    for (i = 0; i < 8; i++)  {
        LCD_SendData(bytes[i]);
    }

// if we added a cgram character without entering cgram mode first, go back to our starting location in DDRAM
#ifdef LCD_MAINTAIN_STATE
    if (changeBack) {
        LCD_GotoXY(_LCD_Pos_X, _LCD_Pos_Y);
    }
#endif

}


// Enter a custom character into cgram
void LCD_SetCGRAMCharROM(unsigned char index, rom const char *bytes) {
    unsigned char i;

//  If we are not already in cgram mode, switch to it before adding the new characters
#ifdef LCD_MAINTAIN_STATE
    unsigned char changeBack = 0;
    if (!(_LCD_Settings & LCD_SETTING_DDRAM_MODE)) {
        changeBack = 1;
    }
#endif

    LCD_SetCGRAMAddr(index * 8);

    for (i = 0; i < 8; i++)  {
        LCD_SendData(bytes[i]);
    }

// if we added a cgram character without entering cgram mode first, go back to our starting location in DDRAM
#ifdef LCD_MAINTAIN_STATE
    if (changeBack) {
        LCD_GotoXY(_LCD_Pos_X, _LCD_Pos_Y);
    }
#endif

}







/**************************************************************************
 *     LCD State maintainance functions - Allows for a bit higher level interface
 *     with the LCD by keeping track of settings so you do not have to keep resetting
 *     all other settings in order to change another in its associated command
 ***************************************************************************************/


#ifdef LCD_MAINTAIN_STATE

// activate/deactivate the display keeping cursor properties at their previous state
void LCD_ActivateDisplay(bool act) {
     unsigned char cmd = LCD_CMD_DSIPLAY_CNTL;

    // if we want the cursor to go right
    if (act) {

        // turn on the display
        cmd |= LCD_DISPLAY_ON;

        // and store the setting
        _LCD_Settings |= LCD_SETTING_DISPLAY_ON;
    }
    else {
        // otherwise store the inverse setting
        _LCD_Settings &= ~LCD_SETTING_DISPLAY_ON;
    }

    // make sure the display and blink settings are maintained
    if (_LCD_Settings &= LCD_SETTING_SHOW_CURSOR) {
        cmd |= LCD_DISPLAY_CURSOR_ON;
    }

    if (_LCD_Settings &= LCD_SETTING_CURSOR_BLINK) {
        cmd |= LCD_DISPLAY_CURSOR_BLINK_ON;
    }

    LCD_WaitForNotBusy();
    LCD_WriteCommand(cmd);
}


// switch on or off display shifting  (maintains state)
void LCD_SetDisplayShift(bool shift) {
    unsigned char cmd = LCD_CMD_SET_ENTRY_MODE;

    if (shift) {
        cmd |= LCD_ENTRY_SHIFT;
        _LCD_Settings |= LCD_SETTING_DISPLAY_SHIFT;
    }
    else {
        _LCD_Settings &= ~LCD_SETTING_DISPLAY_SHIFT;
    }

    // maintain the cursor movement mode
    if (_LCD_Settings & LCD_SETTING_CURSOR_INC) {
        cmd |= LCD_ENTRY_INCREMENT;
    }

    LCD_WaitForNotBusy();
    LCD_WriteCommand(cmd);
}


// changes cursor movement  (maintains state)
void LCD_SetCursorMovement(LCD_CURSOR_DIRECTION dir) {
    unsigned char cmd = LCD_CMD_SET_ENTRY_MODE;

    // if we want the cursor to go right
    if (dir == LCD_CURSOR_RIGHT) {

        // set the command to increment
        cmd |= LCD_ENTRY_INCREMENT;

        // and store the setting
        _LCD_Settings |= LCD_SETTING_CURSOR_INC;
    }
    else {
        // otherwise store the inverse setting
        _LCD_Settings &= ~LCD_SETTING_CURSOR_INC;
    }

    // make sure the display shift setting is set to the stored value
    if (_LCD_Settings &= LCD_SETTING_DISPLAY_SHIFT) {
        cmd |= LCD_ENTRY_SHIFT;
    }

    LCD_WaitForNotBusy();
    LCD_WriteCommand(cmd);
}


// changes cursor appearance  (maintains state)
void LCD_ShowCursor(bool cur) {
    unsigned char cmd = LCD_CMD_DSIPLAY_CNTL;

    // if we want the cursor to go right
    if (cur) {

        // turn on the cursor
        cmd |= LCD_CURSOR_ON;

        // and store the setting
        _LCD_Settings |= LCD_SETTING_SHOW_CURSOR;
    }
    else {
        // otherwise store the inverse setting
        _LCD_Settings &= ~LCD_SETTING_SHOW_CURSOR;
    }

    // make sure the display and blink settings are maintained
    if (_LCD_Settings &= LCD_SETTING_DISPLAY_ON) {
        cmd |= LCD_DISPLAY_ON;
    }

    if (_LCD_Settings &= LCD_SETTING_CURSOR_BLINK) {
        cmd |= LCD_CURSOR_BLINK_ON;
    }

    LCD_WaitForNotBusy();
    LCD_WriteCommand(cmd);
}


// changes cursor movement  (maintains state)
void LCD_BlinkCursor(bool cur) {
    unsigned char cmd = LCD_CMD_DSIPLAY_CNTL;

    // if we want the cursor to go right
    if (cur) {

        // turn on the cursor
        cmd |= LCD_DISPLAY_CURSOR_BLINK_ON;

        // and store the setting
        _LCD_Settings |= LCD_SETTING_CURSOR_BLINK;
    }
    else {
        // otherwise store the inverse setting
        _LCD_Settings &= ~LCD_SETTING_CURSOR_BLINK;
    }

    // make sure the display and blink settings are maintained
    if (_LCD_Settings &= LCD_SETTING_DISPLAY_ON) {
        cmd |= LCD_DISPLAY_ON;
    }

    if (_LCD_Settings &= LCD_SETTING_SHOW_CURSOR) {
        cmd |= LCD_SETTING_SHOW_CURSOR;
    }

    LCD_WaitForNotBusy();
    LCD_WriteCommand(cmd);

}



#endif

