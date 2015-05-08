/* 
 * File:   Filler_PSpeedTable.h
 * Author: pulam
 *
 * Created on February 7, 2013, 4:35 PM
 */

#ifndef PFILLER_SPEEDTABLE_H
#define	PFILLER_SPEEDTABLE_H


// A filling profile is a series of weight -> speed entries indicating at what level the DAC should output
//    when the weight is at a particular value.  Each entry is 2-bytes (16 bits) where each entry is formatted
//    as: ssssswww wwwwwwww  where s = speed and w = weight value
//    This gives us enough accuracy to output a DAC level for any weight up to 2047g at 1 gram resolution
//    which should be sufficient for our purposes


#define SPEED_TABLE_HIGH_ADDRESS        0x60
#define SPEED_TABLE_LOW_ADDRESS         0x00


// The list of weight/speed points used to control the feeder for a particular substance
// each item has an index so we can read its data from program memory, a 20 character descriptor to show on the lcd, and a table for 22 weight set points
// this is likely more resolution than we need but we wanted to get this to 64 bytes to make writing to program memory easy
extern unsigned char _CurItemIndex;

// the number of preset feeder table entries
extern int _MaxFeederItems;

// the index of the last weight in the speed table so we can find where we need to go quickly,   since weight left to fill will be monotonically decreasing
// -1 indicates that this is the first search into the table entry
extern signed char _LastWeightIndex;


// program memory is made of 64 byte pages so we will make each entry 64 bytes to make saving and reading easy     Weights will go from lowest remaining to highest remaining
typedef struct  {
    char _ItemDescStr[20];
    unsigned short _ItemSpeedTable[22];
} FeederControlTable_t;

extern FeederControlTable_t _FeederControlTable;            // The master table describing the speeds to run the filler for each item at each weight

// array of string representations for the 32 different speeds available to the filler (in percentages  x/32);
extern rom const char *_SpeedStr[];


// temp function to build the weight speed tables
void Make_WeightSpeedEntries(void);

// load the weight speed table entry at index into memory (making it the active control table)
void Load_WeightSpeedTableEntry(unsigned char index);

// save the current weight speed table entry into index of the the master weight speed table
void Save_WeightSpeedTableEntry(unsigned char index);


// functions to load the next and previous entries in the master speed table (corresponding to material type (fine, coarse, etc))
void Load_NextItemSpeedTable(void);
void Load_PrevItemSpeedTable(void);

// functions to load the next and previous entries in the preset weight table (1oz, 4oz, etc)
void Load_NextPresetWeight(void);
void Load_PrevPresetWeight(void);


void Create_CustomWeightStr(void);
void Convert_SelectedWeightToStr(unsigned char *str);

// return the speed the feeder should run given the weight stored in _FeederScale
unsigned char Get_FeederSpeed(void);


// the number of weight presets available
#define MAX_PRESET_WEIGHTS    7
extern unsigned char _SelectedPresetWeight;                     // the current weight preset selected



#endif	/* PFILLER_SPEEDTABLE_H */

