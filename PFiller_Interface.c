#include "stdbool.h"
#include <string.h>
#include "PFiller_Globals.h"
#include "PFiller_SpeedTable.h"


// string containing the version of the filler software
const rom char _PFillFirmwareVersion[] = "0.90";


// custom character for displaying a bar graph for progress
const rom char _CustChar1[8] = {0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000};


const rom char _CustChar2[8] = {0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000};

const rom char _CustChar3[8] = {0b00011100,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011100,
    0b00011100};

const rom char _CustChar4[8] = {0b00011110,
    0b00011110,
    0b00011110,
    0b00011110,
    0b00011110,
    0b00011110,
    0b00011110,
    0b00011110};

const rom char _CustChar5[8] = {0b00011111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00011111};


// custom character for the splash
const rom char _CustChar6[8] = {0b00000010,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00011110,
    0b00001110,
    0b00001100};



// various template strings for the splash
const rom char _PFillTitleName[] = "P Filler";
const rom char _PFillTitleVersion[] = "Version ";
//const rom char _WeightTemplateStr[] = "      . g  Spd: 100%";


char _WeightDescStr[19] = {0};
char _StatusStr[21] = {0};

unsigned char _FootPedalBounceCnt = 0;
unsigned char _LCDUpBounceCnt = 0;
unsigned char _LCDDownBounceCnt = 0;
unsigned char _LCDSelectBounceCnt = 0;
unsigned char _ButtonState = 0;
unsigned char _ExecuteButtonActions = 0;
unsigned char _FootPedalRelease = 0;


unsigned char _InterfaceState = 0x00;

void Check_ButtonState(void) {

    // pins are normally pulled up to 5v

    unsigned char curButtons = 0;

    // determine the state of all our buttons
    if (FOOT_PEDAL_PIN == 1) {
        
        // we do not want to trigger the foot pedal more than once without it being released first
        //if (_FootPedalRelease == 0) {
            curButtons = BUTTON_FOOT_PEDAL_PRESSED;


            _FootPedalBounceCnt++;

            if (_FootPedalBounceCnt == 40) _FootPedalBounceCnt = 39;
       // }
    }
    else if (LCD_UP_BUTTON_PIN == 0) {
        curButtons = BUTTON_LCD_UP_PRESSED;
        _LCDUpBounceCnt++;
    }
    else if (LCD_DOWN_BUTTON_PIN == 0) {
        curButtons = BUTTON_LCD_DOWN_PRESSED;
        _LCDDownBounceCnt++;
    }
    else if (LCD_SELECT_BUTTON_PIN == 0) {
        curButtons = BUTTON_LCD_SELECT_PRESSED;
        _LCDSelectBounceCnt++;
    }

    // if the states between two checks do not match up, clear the debouncing counter
    if ((curButtons & BUTTON_FOOT_PEDAL_PRESSED) != (_ButtonState & BUTTON_FOOT_PEDAL_PRESSED)) {
        _FootPedalBounceCnt = 0;
        _FootPedalRelease = 0;                  // the foot pedal has been released so we can trigger it again
    }
    if ((curButtons & BUTTON_LCD_UP_PRESSED) != (_ButtonState & BUTTON_LCD_UP_PRESSED)) {
        _LCDUpBounceCnt = 0;
        _InterfaceState &= ~INTERFACE_AUTO_REPEAT_TRIGGERED; // any auto repeat ends along with the button release
    }
    if ((curButtons & BUTTON_LCD_DOWN_PRESSED) != (_ButtonState & BUTTON_LCD_DOWN_PRESSED)) {
        _LCDDownBounceCnt = 0;
        _InterfaceState &= ~INTERFACE_AUTO_REPEAT_TRIGGERED; // any auto repeat ends along with the button release
    }
    if ((curButtons & BUTTON_LCD_SELECT_PRESSED) != (_ButtonState & BUTTON_LCD_SELECT_PRESSED)) {
        _LCDSelectBounceCnt = 0;
    }

    // execute the foor bedal press
    if (_FootPedalBounceCnt == (BUTTON_BOUNCE_CYCLES + 15)) {
        //if (_FootPedalRelease == 0) {                           // we only want to execute the foot pedal once if it is held down.  We can trigger it again once it has been released
            _ExecuteButtonActions |= BUTTON_FOOT_PEDAL_PRESSED;
       // }
    }



    // all other buttons can not be activated when the filler is running
    if (!(_FillerStatus & FILLER_RUNNING)) {

        if (_LCDUpBounceCnt >= BUTTON_BOUNCE_CYCLES) {
            // after 1 second (100 10ms button check cycles of the button being pressed
            if (_InterfaceState & INTERFACE_CUSTOM_WEIGHT) {
                if (!(_InterfaceState & (INTERFACE_WAITING_FOR_AUTO_REPEAT | INTERFACE_AUTO_REPEAT_TRIGGERED))) {
                    _ExecuteButtonActions |= BUTTON_LCD_UP_PRESSED;
                    _InterfaceState |= INTERFACE_WAITING_FOR_AUTO_REPEAT;
                }
                else {

                    if (_LCDUpBounceCnt == 100) {

                        // we go into auto repeat mode:  useful for changing the custom weight
                        _InterfaceState |= INTERFACE_AUTO_REPEAT_TRIGGERED;
                        _InterfaceState &= ~INTERFACE_WAITING_FOR_AUTO_REPEAT;
                        _LCDUpBounceCnt = BUTTON_BOUNCE_CYCLES; //  decrease the bounce count so we remain triggered through auto repeat
                    }

                    // if we are in auto repeat mode every time through we trigger the action
                    if (_InterfaceState & INTERFACE_AUTO_REPEAT_TRIGGERED) {
                        _ExecuteButtonActions |= BUTTON_LCD_UP_PRESSED;
                        _LCDUpBounceCnt = BUTTON_BOUNCE_CYCLES + 1;
                    }
                }
            }                // and if we are on our first time through (before we start waiting on the auto repeat
                //      we trigger the action
            else if (_LCDUpBounceCnt == BUTTON_BOUNCE_CYCLES) {
                _ExecuteButtonActions |= BUTTON_LCD_UP_PRESSED;
            }
        }
        else if (_LCDDownBounceCnt >= BUTTON_BOUNCE_CYCLES) {
            // after 1 second (100 10ms button check cycles of the button being pressed
            if (_InterfaceState & INTERFACE_CUSTOM_WEIGHT) {
                if (!(_InterfaceState & (INTERFACE_WAITING_FOR_AUTO_REPEAT | INTERFACE_AUTO_REPEAT_TRIGGERED))) {
                    _ExecuteButtonActions |= BUTTON_LCD_DOWN_PRESSED;
                    _InterfaceState |= INTERFACE_WAITING_FOR_AUTO_REPEAT;
                } else {

                    if (_LCDDownBounceCnt == 100) {

                        // we go into auto repeat mode:  useful for changing the custom weight
                        _InterfaceState |= INTERFACE_AUTO_REPEAT_TRIGGERED;
                        _InterfaceState &= ~INTERFACE_WAITING_FOR_AUTO_REPEAT;
                        _LCDDownBounceCnt = BUTTON_BOUNCE_CYCLES; //  decrease the bounce count so we remain triggered through auto repeat
                    }

                    // if we are in auto repeat mode every time through we trigger the action
                    if (_InterfaceState & INTERFACE_AUTO_REPEAT_TRIGGERED) {
                        _ExecuteButtonActions |= BUTTON_LCD_DOWN_PRESSED;
                        _LCDDownBounceCnt = BUTTON_BOUNCE_CYCLES + 1;
                    }
                }
            }                // and if we are on our first time through (before we start waiting on the auto repeat
                //      we trigger the action
            else if (_LCDDownBounceCnt == BUTTON_BOUNCE_CYCLES) {
                _ExecuteButtonActions |= BUTTON_LCD_DOWN_PRESSED;
            }
        } else if (_LCDSelectBounceCnt == BUTTON_BOUNCE_CYCLES) {
            _ExecuteButtonActions |= BUTTON_LCD_SELECT_PRESSED;
        }

    }
    // we will now compare the sensed state next cycle to the current state this cycle
    _ButtonState = curButtons;
}

void Start_FillCycle(void) {

    _FeederSpeed = 0; // set the speed to 0 as we are either pausing or just starting the feeder

    // if the filler is running, pause the filler on a foot press
    if (_FillerStatus & FILLER_RUNNING) {
        _FillerStatus &= ~FILLER_RUNNING;
        _FillerStatus |= FILLER_PAUSED;
        VREFCON2 = 0; // actually turn off the dac
        strcpypgm2ram(_StatusStr, (rom far char*)"   Filling Paused   "); // show a status message describing the error
        _StatusStr[20] = 0;
        Draw_Status();
    }
        // if the filler is paused, unpause it
    else if (_FillerStatus & FILLER_PAUSED) {
        _FillerStatus = FILLER_RUNNING;
        Scale_Request_Weight();
    }        // if it is not filling or paused then we start a fill cycle
    else {
        // we will redraw the screen to make things easier
        LCD_ClearScreen();

        Draw_FeederItem(); // draw the item we will be filling

        // for the fill cycle we are just going to have the numeric representation of the target weight displayed so we can compare it
        //    the display of the current weight
        memset(_WeightDescStr, 32, 20);
        Create_CustomWeightStr();
        Draw_TargetPresetWeight();

        // clear out the current weight and status line
        LCD_GotoXY(0, 2);
        LCD_WriteStringROM("     0.0g   Sp:     ");
        LCD_GotoXY(0, 3);
        LCD_WriteStringROM("      Starting      ");

        // set the filler to running and set the speed table index to -1 so we know to search table for the correct starting point
        _FillerStatus = FILLER_RUNNING;
        _LastWeightIndex = -1;

        // the fill cycle begins with the taring of the scale
        Scale_Request_Tare();
    }
}


// checks for button actions that need to be executed

void Handle_ButtonPresses(void) {

    // we begin or pause a fill cycle if execute a foot pedal press action
    if (_ExecuteButtonActions & BUTTON_FOOT_PEDAL_PRESSED) {
        //if (_FootPedalRelease == 0) {
            _FootPedalRelease = 1;                      // mark the foot pedal pressed so we can avoid double activation if it is held down
            Start_FillCycle();
            _ExecuteButtonActions = 0;
        //}
    }

    // go to the next item, higher weight

    if (_ExecuteButtonActions & BUTTON_LCD_UP_PRESSED) {

        // clear the action
        _ExecuteButtonActions = 0;

        // if we are not in configuration mode, redraw the screen (to clear old status messages) and enter config mode
        if (_FillerStatus & FILLER_FINISHED_CYCLE) {
            _FillerStatus = FILLER_CONFIGURING;
            strcpypgm2ram(_StatusStr, (rom far char*)" Set Filler Params");
            Redraw_Interface();
        }

        // we do not execute this action if the filler is running or paused
        else if (_FillerStatus & (FILLER_PAUSED | FILLER_RUNNING)) {
            return;
        }

        if (_InterfaceState & INTERFACE_TYPE_SELECTION) {

            Load_NextItemSpeedTable();
            Draw_FeederItem();
        }
        else if (_InterfaceState & INTERFACE_WEIGHT_SELECTION) {
            Load_NextPresetWeight();
            Draw_TargetPresetWeight();
        }
            // this is the custom weight entry need to allow for keeping key down
        else {
            if (_TargetWeight >= (short) 30000) {
                _TargetWeight = 10;
            } else {
                _TargetWeight += 10;
            }

            Draw_CustomWeight();
        }
    }

    // Down/Right button
    if (_ExecuteButtonActions & BUTTON_LCD_DOWN_PRESSED) {

        // clear the action
        _ExecuteButtonActions = 0;

        // if we are not in configuration mode, redraw the screen (to clear old status messages) and enter config mode
        if (_FillerStatus & FILLER_FINISHED_CYCLE) {
            _FillerStatus = FILLER_CONFIGURING;
            strcpypgm2ram(_StatusStr, (rom far char*)" Set Filler Params");
            Redraw_Interface();
        }

        // we do not execute this action if the filler is running or paused
        else if (_FillerStatus & (FILLER_PAUSED | FILLER_RUNNING)) {
            return;
        }

        // if we are at the item selection menu, pressing select will move the interface to the weight selection
        if (_InterfaceState & INTERFACE_TYPE_SELECTION) {
            Load_PrevItemSpeedTable();
            Draw_FeederItem();
        }
            // if we are at weight selection but are not at entering the custom weight, go to custom weight selection
        else if (_InterfaceState & INTERFACE_WEIGHT_SELECTION) {
            Load_PrevPresetWeight();
            Draw_TargetPresetWeight();
        }
            // if we are in the custom weight selection, we decrease the custom weight
        else {
            if (_TargetWeight < (short) 0) {
                _TargetWeight = 30000;
            } else {
                _TargetWeight -= 10;
            }
            Draw_CustomWeight();
        }
    }

    if (_ExecuteButtonActions & BUTTON_LCD_SELECT_PRESSED) {

        // clear the action
        _ExecuteButtonActions = 0;

        // if we are not in configuration mode, redraw the screen (to clear old status messages) and enter config mode
        if (_FillerStatus & FILLER_FINISHED_CYCLE) {
            _FillerStatus =- FILLER_CONFIGURING;
            strcpypgm2ram(_StatusStr, (rom far char*)" Set Filler Params");
            Redraw_Interface();
        }

        // we do not execute this action if the filler is running or paused
        else if (_FillerStatus & (FILLER_PAUSED | FILLER_RUNNING)) {
            return;
        }

        // if we are at the item selection menu, pressing select will move the interface to the weight selection
        if (_InterfaceState & INTERFACE_TYPE_SELECTION) {
            _InterfaceState |= INTERFACE_WEIGHT_SELECTION;
            _InterfaceState &= ~INTERFACE_TYPE_SELECTION;
            Draw_InterfaceSelection();
        }            // if we are in the weight selection, we would now switch to custom weight
        else if (_InterfaceState & INTERFACE_WEIGHT_SELECTION) {
            _InterfaceState &= ~INTERFACE_WEIGHT_SELECTION;
            _InterfaceState |= INTERFACE_CUSTOM_WEIGHT;
            Draw_InterfaceSelection();
        }            // if we are at custom weight selection so go back to item selection
        else {
            _InterfaceState &= ~INTERFACE_CUSTOM_WEIGHT;
            _InterfaceState |= INTERFACE_TYPE_SELECTION;
            Draw_InterfaceSelection();
        }
    }
}

void Init_FillerDisplay(void) {
    LCD_SetCGRAMCharROM(0, _CustChar6);

    LCD_GotoXY(4, 0);
    LCD_WriteChar(0); // show our custom char for splash
    LCD_WriteStringROM(_PFillTitleName);

    LCD_GotoXY(4, 2);
    LCD_WriteStringROM(_PFillTitleVersion);

    LCD_WriteStringROM(_PFillFirmwareVersion);

    // clear out two buffers used in the display
    memset(_WeightDescStr, 0, 18);
    memset(_StatusStr, 0, 20);

    strcpypgm2ram(_StatusStr, (rom far char*)" Set Filler Params");

    // Set up the rest of our custom characters used for the bar graph
    LCD_SetCGRAMCharROM(1, _CustChar1);
    LCD_SetCGRAMCharROM(2, _CustChar2);
    LCD_SetCGRAMCharROM(3, _CustChar3);
    LCD_SetCGRAMCharROM(4, _CustChar4);
    LCD_SetCGRAMCharROM(5, _CustChar5);
}

// draw the selection icon for the interface
void Draw_InterfaceSelection(void) {
    unsigned char i = 0;

    if (_InterfaceState & INTERFACE_TYPE_SELECTION) {
        LCD_GotoXY(0, 0);
        LCD_WriteChar(126);
        LCD_GotoXY(0, 1);
        LCD_WriteChar(' ');
        LCD_GotoXY(0, 2);
        for (i = 0; i < 20; i++) {
            LCD_WriteChar(' ');
        }
    }
    else {
        LCD_GotoXY(0, 0);
        LCD_WriteChar(' ');
        LCD_GotoXY(0, 1);
        LCD_WriteChar(126);


        if (_InterfaceState & INTERFACE_WEIGHT_SELECTION) {
            LCD_GotoXY(0, 2);
            for (i = 0; i < 20; i++) {
                LCD_WriteChar(' ');
            }
        }
        else {
            Draw_CustomWeight();
            LCD_GotoXY(0, 2);
            LCD_WriteStringROM("Select Custom Weight");
        }
    }
}


// draw the current item type selected by the feeder
void Draw_FeederItem(void) {
    LCD_GotoXY(2, 0);
    LCD_WriteStringLenRAM(_FeederControlTable._ItemDescStr, 18);
}


// draw the current target weight on the lcd
void Draw_TargetPresetWeight(void) {
    LCD_GotoXY(2, 1);
    LCD_WriteStringLenRAM(_WeightDescStr, 18);
}


// draw the custom target weight to the lcd
void Draw_CustomWeight(void) {
    memset(_WeightDescStr, 32, 18);
    Create_CustomWeightStr();
    LCD_GotoXY(2, 1);
    LCD_WriteStringLenRAM(_WeightDescStr, 18);
}


// draw the current weight measured by the operating feeder
void Draw_CurrentWeight(void) {
    LCD_GotoXY(2, 2);
    LCD_WriteStringLenRAM(&_FeederScale._WeightStr[3], 7);
}

// draw the current speed as a percentage of maximum
void Draw_Speed(void) {
    LCD_GotoXY(16, 2);
    LCD_WriteStringLenROM(_SpeedStr[_FeederSpeed], 4);
}

// draw the status string
void Draw_Status(void) {
    LCD_GotoXY(0, 3);
    LCD_WriteStringRAM(_StatusStr);
}

// Redraws all interface elements on the LCD
void Redraw_Interface(void) {
    LCD_ClearScreen();

    Draw_InterfaceSelection();
    Draw_FeederItem();
    Draw_TargetPresetWeight();
    Draw_Status();
}


void Draw_ProgressBar(void) {
    unsigned char t;
    unsigned char index = 0;
    long cnt = 0;

    long scaledWeight = (_FeederScale._Weight) * 100;
    long fivePer = _TargetWeight * 5;

    memset(_StatusStr, 32, 20);

    // for each 5 percent we have filled fill in one whole bar of the progress graph
    while (cnt + fivePer < scaledWeight) {
        cnt += fivePer;
        _StatusStr[index++] = 5;
    }
    
    t = 0;
    
    cnt += _TargetWeight;
    if (cnt < scaledWeight) t++;
    cnt += _TargetWeight;
    if (cnt < scaledWeight) t++;
    cnt += _TargetWeight;
    if (cnt < scaledWeight) t++;
    cnt += _TargetWeight;
    if (cnt < scaledWeight) t++;
  
    if (t != 0) {
        _StatusStr[index] = t;
    }
    _StatusStr[20] = 0;

    LCD_GotoXY(0, 3);
    LCD_WriteStringRAM(_StatusStr);
}



