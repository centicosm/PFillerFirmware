/* 
 * File:   PLCD_Settings.h
 * Author: pulam
 *
 * Application specific setting necessary to use the LCD libray.  Set these
 *      values as appropriate for you chip configuration
 */

#ifndef PLCD_SETTINGS_H
#define	PLCD_SETTINGS_H

// when defined, stores some state variables and cursor location and allows changing one element of the display 
//     configuration without having to reset all related configuration elements  (e.g. it will allow setting the 
//     cursor to blinking without having to respecify that is should be displayed
#define LCD_MAINTAIN_STATE


//#define LCD_1_LINE
//#define LCD_2_LINE
#define LCD_4_LINE


// Define this if the LCD will only be using write operations (e.g. the R/W flag is tied low)
#define LCD_WRITE_ONLY


#define LCD_CHAR_PER_LINE   20


// Define the interface to the lcd as 8-bit or 4-bit (by commenting out this define)
//#define LCD_INTERFACE_8_BIT

// When in 4-bit interface define if the data is in the upper
// or lower nibble.  For lower nibble, comment the #define UPPER
#define LCD_4_BIT_UPPER_NIBBLE
//#define LCD_4_BIT_LOWER_NIBBLE





// DATA_PORT defines the port to which the LCD data lines are connected
#define LCD_DATAPORT      		PORTA
#define LCD_DATAPORT_TRIS 		TRISA

//
#define LCD_BUSY                        PORTAbits.RA7
#define LCD_BUSY_TRIS                   TRISAbits.TRISA7

// Locations of the different control pins for the lcd
#define LCD_RS                         LATAbits.LATA0
#define LCD_RS_TRIS                    TRISAbits.TRISA0

#define LCD_RW                         LATAbits.LATA1
#define LCD_RW_TRIS                    TRISAbits.TRISA1

#define LCD_E                          LATAbits.LATA3
#define LCD_E_TRIS                     TRISAbits.TRISA3


#endif	/* PLCD_SETTINGS_H */

