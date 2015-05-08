/* 
 * File:   PFeederInterface.h
 * Author: pulam
 *
 * Created on February 4, 2013, 12:10 PM
 */

#ifndef PFILLER_INTERFACE_H
#define	PFILLER_INTERFACE_H

#include "p18f25k50.h"

#define BUTTON_BOUNCE_CYCLES          3              // number of 10ms cycles to wait to determine if a button is done bouncing

#define BUTTON_FOOT_PEDAL_PRESSED     0b00000001
#define BUTTON_LCD_UP_PRESSED         0b00000010
#define BUTTON_LCD_DOWN_PRESSED       0b00000100
#define BUTTON_LCD_SELECT_PRESSED     0b00001000
#define BUTTON_RESET_PRESSED          0b00010000

#define FOOT_PEDAL_PIN                       PORTBbits.RB0
#define FOOT_PEDAL_PIN_TRIS                  TRISBbits.TRISB0

#define LCD_UP_BUTTON_PIN                    PORTBbits.RB1
#define LCD_UP_BUTTON_TRIS                   TRISBbits.TRISB1
#define LCD_DOWN_BUTTON_PIN                  PORTBbits.RB2
#define LCD_DOWN_BUTTON_TRIS                 TRISBbits.TRISB2
#define LCD_SELECT_BUTTON_PIN                PORTBbits.RB3
#define LCD_SELECT_BUTTON_TRIS               TRISBbits.TRISB3


extern unsigned char _InterfaceState;


extern unsigned char _FootPedalBounceCnt;
extern unsigned char _LCDUpBounceCnt;
extern unsigned char _LCDDownBounceCnt;
extern unsigned char _LCDSelectBounceCnt;
extern unsigned char _ButtonState;
extern unsigned char _ExecuteButtonActions;

extern char _WeightDescStr[19];           // the buffer used to store the target weight string for the LCD
//extern char _CurWeightStr[21];            // the buffer used to store the curent weight string for the LCD
extern char _StatusStr[21];               // the buffer used to store the feeder status/progress for the LCD

#define INTERFACE_TYPE_SELECTION        0b00000001
#define INTERFACE_WEIGHT_SELECTION      0b00000010
#define INTERFACE_CUSTOM_WEIGHT         0b00000100            // flag indicating that the preset weight index is invalid and the user
#define INTERFACE_AUTO_REPEAT_TRIGGERED 0b00001000            // flag indicating that the button has been pressed long
                                                              //   enough to start the auto repeat

#define INTERFACE_WAITING_FOR_AUTO_REPEAT  0b00010000            // flag indicating that we are waiting to see if we should activate the auto repeat

//     selected a custom weight
void Init_FillerDisplay(void);
void Redraw_Interface(void);
void Update_Interface(void);
void Draw_ProgressBar(void);
void Draw_InterfaceSelection(void);
void Draw_FeederItem(void);
void Draw_TargetPresetWeight(void);
void Draw_CustomWeight(void);
void Draw_CurrentWeight(void);
void Draw_Speed(void);
void Draw_Status(void);

void Check_ButtonState(void);
void Handle_ButtonPresses(void);

void Make_WeightSelectedStr(void);


#endif

