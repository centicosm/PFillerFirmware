/* 
 * File:   PScale.h
 * Author: pulam
 *
 * Created on February 1, 2013, 8:26 AM
 */

#ifndef PSCALE_H
#define	PSCALE_H


// scale command strings
#define PSCALE_CMD_TARE         't'
#define PSCALE_CMD_WEIGH        's'

// scale state flags
#define SCALE_TARE_CMD_IN_PROGRESS      0b00000010              // Waiting for the ack from the scale
#define SCALE_WEIGH_CMD_IN_PROGRESS     0b00000100              // Reading a weight string from the scale
#define SCALE_WEIGHT_READY              0b00001000              // Complete weight has been read from scale, now ready for processing

// structure used to store all our scale and weight information read from the scale
typedef struct Scale_t  {
    unsigned char _Status;              // keeps track of the communication state of the scale
    unsigned char _WeightStr[14];       // buffer for storing characters received from the scale
    short _Weight;                      // an actual numeric weight received by the scale  (it is in decigrams)
} Scale;


extern Scale _FeederScale;              // the actual variable used to store the scale data

void Init_Scale(void);
void Scale_Request_Weight(void);
void Scale_Request_Tare(void);
void Read_Scale_Data(void);
void Convert_ScaleString(void);


#endif	/* PSCALE_H */

