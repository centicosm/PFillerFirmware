/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <string.h>
#include "PFiller_Globals.h"
#include "PFiller_SpeedTable.h"


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void) {
    unsigned char x;
    unsigned char i = 0;

  // Uncomment this function to rebuild the weight/speed mapping table in flash
   // Make_WeightSpeedEntries();

     // load the very first weight and speed mapping from flash memory.
     Load_WeightSpeedTableEntry(0);


    // Initialize filler, periphrials, and interrupts
    Init_Filler();

//    TRISAbits.RA2 = OUTPUT_TRIS;             // RA2 is our dac so it is an output
 
//    VREFCON1 = 0b11100000;

  //  VREFCON2 = 16;                 // this should be zero at initialization
    // main activity loop
    while(1) {
        
        // if the filler is in a filler cycle
        if (_FillerStatus & FILLER_RUNNING) {

            // if the weight is done immediately convert it into a numeric value
            if (_FeederScale._Status & SCALE_WEIGHT_READY) {

                // change the ascii weight to a number
                Convert_ScaleString();
                Draw_CurrentWeight();
                
                // check it against the target weight
                if ((_TargetWeight - _FeederScale._Weight) <= 0) {

                    // if we have gotten to the target weight or beyond, stop the filler
                    VREFCON2 = 0;                       // DAC at 0v
                    _FillerStatus = FILLER_FINISHED_CYCLE;    // filler is done running
                    Draw_Speed();
                    strcpypgm2ram(_StatusStr, (rom far char*)"  Filling Finished  ");
                    _StatusStr[20] = 0;
                    Draw_Status();
                }

                // otherwise we set the speed based on how much weight remains to be filled
                else {

                    // look up the new speed based on the weight just read
                    _FeederSpeed = Get_FeederSpeed();
                    VREFCON2 = _FeederSpeed;                    // set the speed via dac
                    Draw_Speed();                               // draw the current speed
                    Draw_ProgressBar();                         // draw the progress bar

                    Scale_Request_Weight();                     // and start another weigh request
                }
            }
        }

        // if we got an ack from the tare command indicating the filler is initialized
        //    start the filler by requesting the first weight
        else if (_FillerStatus & FILLER_INITIALIZED) {
            Scale_Request_Weight();
            _FillerStatus &= ~FILLER_INITIALIZED;
            _FillerStatus |= FILLER_RUNNING;
        }

        // handle any button presses
        Handle_ButtonPresses();
    }
}

