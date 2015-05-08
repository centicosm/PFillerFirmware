/* 
 * File:   PFeederController_Globals.h
 * Author: pulam
 *
 *   Master include file (to make including the necessary .h files easier)
 *   and global variablees/defines
 */

#ifndef PFEEDERCONTROLLER_GLOBALS_H
#define	PFEEDERCONTROLLER_GLOBALS_H

#include "PApp_Config.h"
#include "PDelay.h"
#include "PCircularBuffer.h"
#include "PLCD.h"
#include "PSerial_RS232.h"
#include "PScale.h"
#include "PFiller_Interface.h"
#include "PFiller_Init.h"


//   Hardware specific define, for some reason the weak pullups are not defined in the pic18f25k50.h file
//extern volatile unsigned char           WPUB                @ 0xF85;

// -------------------------------------------------------------------------------------------------------------------
extern const rom char _PFillFirmwareVersion[];

#define FILLER_RUNNING                  0b00000010     // the filler is currently in a fill cycle
#define FILLER_PAUSED                   0b00000100     // the filler is in a fill cycle but actual filling is paused
#define FILLER_INITIALIZED              0b00001000     // the scale has been tared and weigh/adjust speed loop should start
#define FILLER_COMMS_FAULT              0b00010000     // we have not received an XOFF in a given amount of time indicating that something is wrong
#define FILLER_CONFIGURING              0b00100000     // we are configuring the filler (Initial state)
#define FILLER_FINISHED_CYCLE           0b01000000     // filler has finished a fill cycle

#define SCALE_SERIAL                    0x01           // id of the scale in case there were multiple

#define SPLASHSCREEN_DURATION           1               // time in HALF SECONDS (2 = 1s) to show the splash screen


extern unsigned char _FillerStatus;                     // contains flags indicating the current state of the feeder (running, initializing, etc)
extern unsigned char _WeightIndex;                      // Currently selected index in the weight preset table
extern short _TargetWeight;                             // The weight we are trying to fill  (0-2047g
extern unsigned char _FeederSpeed;                      // The current speed of the feeder
extern unsigned char _RxIndex;                          // Index to the next free location in the serial receive buffer


#endif	/* PFEEDERCONTROLLER_GLOBALS_H */

