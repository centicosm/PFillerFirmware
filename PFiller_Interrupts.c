// PFiller_Interrupts - The interrupt routine for the filler

//#include <xc.h>
//#include <stdint.h>
#include "stdbool.h"
#include <string.h>
#include "PFiller_Globals.h"

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

unsigned char _RxIndex = 0;
unsigned char _TxIndex = 0;
unsigned char _SerialWatchDog = 0;

#pragma interrupt Service_Interrupt

void Service_Interrupt(void) {
    unsigned char recByte;

     // if timer 0 has gone off, it is time to update all the button states
    if (INTCONbits.TMR0IF) {
        T0CONbits.TMR0ON = false;                // turn off the timer for now
        Check_ButtonState();                    // update the status of all the buttons
        TMR0L = 99;                             // reload the timer to go off afer around 10ms
        TMR0H = 00;
        INTCONbits.TMR0IF = false;              // clear the timer 0 interrupt flag
        T0CONbits.TMR0ON = true;                // turn the timer back on

        // also, ever 10ms we update the watchdog timer
        // if the filler is running we want to make sure we do not end up waiting endlessly for a serial response that does not come
        if (_FillerStatus & FILLER_RUNNING) {
            _SerialWatchDog++;
 
            // if we have been waiting for a serial response for 500ms or more, something has gone wrong
            if (_SerialWatchDog >= 100) {
                VREFCON2 = 0;                           // so turn off the feeder
                _FillerStatus  |= FILLER_COMMS_FAULT | FILLER_PAUSED;   // flag the error and pause the filler
                _FillerStatus &= ~FILLER_RUNNING;       // set the feeder to paused until comms have resumed
                strcpypgm2ram(_StatusStr, (rom far char*)" Serial Comms Lost  ");     // show a status message describin the error
                Draw_Status();
            }
        }

        // if the filler has already faulted, after 1 second we will try to resume automatically be resending the command that was interrupted
        else if (_FillerStatus & FILLER_COMMS_FAULT) {
            _SerialWatchDog++;

            // After we reach 1 second.
            if (_SerialWatchDog >= 200)  {

                _SerialWatchDog = 0;     // reset the watchdog so we can send another message in 1 second

                // resend a tare if we were in the middle of a tare when comms were interrupted
                if (_FeederScale._Status & SCALE_TARE_CMD_IN_PROGRESS) {
                    Scale_Request_Tare();
                }

                // otherwise, resend the weight request if we were in the middle of that
                else {
                    Scale_Request_Weight();
                }
            }
        }      
    }
    
    // The USART receive got an interrupt
    else if (PIR1bits.RCIF) {
        // reset the serial watchdog as we got a valid command
        _SerialWatchDog = 0;

        recByte = RCREG;                  // read the byte from the USART

        //LCD_WriteChar(recByte);
        //return;
        // communications with the scale is very structured so we can throw away the xon flow control
        if (recByte == PSERIAL_XON) {
            _RxIndex = 0;
            return;
        }

        else if (recByte == PSERIAL_XOFF) {

            // if the scale is in the error state, but we receive an xoff, we know comms has resumed so we can start the filler running again
            if (_FillerStatus  & FILLER_COMMS_FAULT) {
                 _FillerStatus &= ~(FILLER_PAUSED | FILLER_COMMS_FAULT);
                 _FillerStatus |= FILLER_RUNNING;
            }


            // if we are performing a weighing command, then the xoff indicates that we have received all the needed characters
            if (_FeederScale._Status & SCALE_WEIGH_CMD_IN_PROGRESS) {
              _FeederScale._WeightStr[_RxIndex] = 0;                        // so terminate the weight string

               // the weigh command is now done and the weight is ready
               _FeederScale._Status &= ~SCALE_WEIGH_CMD_IN_PROGRESS;        // and flag the weight as ready
               _FeederScale._Status |= SCALE_WEIGHT_READY;
            }

            // we are at the end of the tare command.
            else if (_FeederScale._Status & SCALE_TARE_CMD_IN_PROGRESS) {
               _FeederScale._Status &= ~SCALE_TARE_CMD_IN_PROGRESS;
               _FillerStatus |= FILLER_INITIALIZED;                        // the end of a tare indicates that the scale is initialized and ready to start the fill cycle
            }
            return;
        }

        // if the character received is not a XON or XOFF it is a data byte
        // tare ack does not go in the weight buffer
       if (_FeederScale._Status & SCALE_TARE_CMD_IN_PROGRESS) return;
       _FeederScale._WeightStr[_RxIndex] = recByte;
       _RxIndex++;
    }

    // The USART transmit got an interrupt
    else if (PIR1bits.TXIF) {
        _SerialWatchDog = 0;
        TXREG = _TxBuf[_TxIndex++];

        // all our commands are 2 bytes so after we have sent the second byte,
        //      we clear the transmit interrupt enable until we send the next command
        if (_TxIndex == 2) {
            Unflag_Tx();
            _TxIndex = 0;
        }
        // clear the tx interrupt
        PIR1bits.TXIF = false;
    }
}

#pragma code high_vector=0x08
 void high_interrupt(void)
 {
        _asm GOTO Service_Interrupt _endasm
 }
 #pragma code /* return to the default code section */
