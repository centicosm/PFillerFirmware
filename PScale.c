/* 
 * File:   PScale.c
 * Author: pulam
 *
 * Interface with the AWS PN series scale
 */

#include "stdbool.h"
#include "PFiller_Globals.h"

Scale _FeederScale;


// Initialize the any datastructures used by the scale
void Init_Scale(void) {
    _FeederScale._WeightStr[13] = 0;  // null terminate the string so we can just dump it to the lcd
    _FeederScale._Weight  = 0;
    _FeederScale._Status = 0;

}


// tare the scale
void Scale_Request_Tare(void)  {
    _TxBuf[0] = SCALE_SERIAL;
    _TxBuf[1] = PSCALE_CMD_TARE;

    _FeederScale._Status |= SCALE_TARE_CMD_IN_PROGRESS;

    _RxIndex = 0;     // make sure we start filling from the beginning of the receive buffer

    Flag_Tx();
}


// request the weight
void Scale_Request_Weight(void )  {

    _TxBuf[0] = SCALE_SERIAL;
    _TxBuf[1] = PSCALE_CMD_WEIGH;

    _FeederScale._Status |= SCALE_WEIGH_CMD_IN_PROGRESS;

    _RxIndex = 0;     // make sure we start filling from the beginning of the receive buffer
    
    Flag_Tx();
}


// Resolution will always be 1 tenth of a gram so we can throw out unit and decimal
// this also loads up our current weight string buffer used to display the current weight on the LCD
void Convert_ScaleString(void) {

    short weight = 0;

    // this is the maximum weight representable by the weight and the associated positions in the weight string
    //  3  4  5  6 7 8
    //  6  1  0  0 . 0

    // as we can not read over 61000 decigrams we stay within the limits of an unsigned short

    weight += (_FeederScale._WeightStr[7] - 48);    // tenth of a gram
   // _CurWeightStr[7] = _FeederScale._WeightStr[8];
    // ignore decimal
    weight += ((_FeederScale._WeightStr[5] - 48) * 10);     // 1 gram place (10 decigrams)
   // _CurWeightStr[5] = _FeederScale._WeightStr[6];
    weight += ((_FeederScale._WeightStr[4] - 48) * 100);    // 10 gram place (100 decigrams)
   // _CurWeightStr[4] = _FeederScale._WeightStr[5];
    weight += ((_FeederScale._WeightStr[3] - 48) * 1000);    // 100 gram place (1000 decigrams)
  //  _CurWeightStr[3] = _FeederScale._WeightStr[4];
    weight += ((_FeederScale._WeightStr[2] - 48) * 10000);    // 1000 gram place (10000 decigrams)
  //  _CurWeightStr[2] = _FeederScale._WeightStr[3];

    // we are done processing the weight string so save it in our structure and mark the weight ready
    _FeederScale._Weight = weight;
    
    _FeederScale._Status &= ~SCALE_WEIGHT_READY;   // we can unflag the weight as ready now that we have converted it into an int
}
