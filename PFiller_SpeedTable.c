#include "p18f25k50.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include "PFlash.h"
#include "PFiller_SpeedTable.h"
#include "PFiller_Globals.h"

int _MaxFeederItems = 4;

FeederControlTable_t _FeederControlTable;           // the active entry in the weight speed table
signed char _LastWeightIndex = -1;                 // the last speed table entry used (useful for quickly finding the place in the table to start working with)
unsigned char _SelectedPresetWeight = 0;            // current preset weight selected
unsigned char _CurItemIndex = 0;                    // curent feeder weight speed table entry used

rom const char *_WeightStr[] = { "1 oz", "2 oz", "4 oz", "8 oz", "16 oz", "1/2 kg", "1 kg" };    // preset weights in text
const short _WeightVal[] = { 280, 560, 1120, 2260, 4540, 5000, 10000 };   // preset weights in decigrams

// feeder speeds expressed as a percentage  (x/32)
rom const char *_SpeedStr[] = {  "  3%", "  6%", "  9%", " 13%",
                            " 16%", " 19%", " 22%", " 25%",
                            " 28%", " 31%", " 34%", " 38%",
                            " 41%", " 44%", " 47%", " 50%",
                            " 53%", " 56%", " 59%", " 63%",
                            " 66%", " 69%", " 72%", " 75%",
                            " 78%", " 81%", " 84%", " 88%",
                            " 91%", " 94%", " 97%", "100%" };


// loads the weight speed table located at the given index to ram
void Load_WeightSpeedTableEntry(unsigned char index) {

    unsigned short addr = (SPEED_TABLE_HIGH_ADDRESS << 8) | SPEED_TABLE_LOW_ADDRESS;
    addr += (index * 64);

    Flash_Read(addr, (char *)&_FeederControlTable, 64);
}


// Assign the next weight preset and prepare the display string for that weight
void Load_PrevPresetWeight(void) {
    if (_SelectedPresetWeight == 0) {
        _SelectedPresetWeight = MAX_PRESET_WEIGHTS - 1;
    }
    else {
        _SelectedPresetWeight--;
    }
    Make_WeightSelectedStr();
}


// Assign the prev weight preset and prepare the display string for that weight
void Load_NextPresetWeight(void) {
    _SelectedPresetWeight++;
    if (_SelectedPresetWeight == MAX_PRESET_WEIGHTS) {
        _SelectedPresetWeight = 0;
    }
    Make_WeightSelectedStr();
}


// create the display buffer the the current preset weight  Format:   1 oz : 28g
void Make_WeightSelectedStr(void) {
     unsigned char c = 0;
     const rom char *str;

    // blank the selected weight line
    memset(_WeightDescStr, 32, 18);
    _WeightDescStr[18] = 0;

    // then go through and create out own selected weight string
    _TargetWeight = _WeightVal[_SelectedPresetWeight];

    // at the start of the string is the text description
    str = _WeightStr[_SelectedPresetWeight];
    while (str[c] != 0) {
        _WeightDescStr[c] = str[c];
        c++;
    }

    // followed by a numeric description
    _WeightDescStr[c++] = ' ';
    _WeightDescStr[c++] = ':';
    _WeightDescStr[c++] = ' ';
    Convert_SelectedWeightToStr(&_WeightDescStr[c]);
}



// If we are going a custom weight selection, we just want to target convert the weight into text as there is no preset string
void Create_CustomWeightStr(void) {
    unsigned char c = 0;
    Convert_SelectedWeightToStr(&_WeightDescStr[c]);
}


// convert the value in the target weight variable into a string and place it in the passed buffer
void Convert_SelectedWeightToStr(unsigned char *str) {
    unsigned int cnt = 0;
    unsigned short tw = _TargetWeight;

    // blank out the string
    str[0] = str[1]  = str[2] = str[3] = str[4]  = str[5] = str[6] = ' ';

    // thousands place
    while (tw >= 10000u) {
        cnt++;
        tw -= 10000;
    }
    if (cnt != 0u) {
        str[0] = 48 + cnt;
    }
    else {
        str[0] = 32;
    }

    // hundreds place
    cnt = 0;
    while (tw >= (unsigned short)1000) {
        cnt++;
        tw -= 1000;
    }
    if (cnt != (unsigned char)0) {
        str[1] = 48 + cnt;
    }

    // we do not want to show leading zeros
    else if ((unsigned char)str[0] != (unsigned char)32) {
        str[1] = 48;
    }
    else {
        str[1] = 32;
    }
    // tens place
    cnt = 0;
    while (tw >= (unsigned short)100) {
        cnt++;
        tw -= 100;
    }
    if (cnt != (unsigned char)0) {
        str[2] = 48 + cnt;
    }

    // we do not want to show leading zeros
    else if ((unsigned char)str[1] != (unsigned char)32) {
        str[2] = 48;
    }
    else {
        str[2] = 32;
    }

    cnt = 0;
    while (tw >= (unsigned short)10) {
        cnt++;
        tw -= 10;
    }

    // ones place
    str[3] = 48 + cnt;
    
    str[4] = '.';
    str[5] = '0';
    str[6] = 'g';
            
    // str now contains the string rep of any number 0 to 9999
}


// load the next item in the item/speed table
void Load_NextItemSpeedTable(void) {

    _CurItemIndex++;
    if (_CurItemIndex == _MaxFeederItems) {
        _CurItemIndex = 0;
    }

    Load_WeightSpeedTableEntry(_CurItemIndex);
}


// load the previous item in the item/speed table
void Load_PrevItemSpeedTable(void) {

    if (_CurItemIndex == 0) {
        _CurItemIndex = _MaxFeederItems - 1;
    }
    else {
        _CurItemIndex--;
    }
    
    Load_WeightSpeedTableEntry(_CurItemIndex);
}


// given a weight, use the weight/speed table to determine the speed of the feeder.
//   the speed will be the speed from the first set point above the given weight
unsigned char Get_FeederSpeed(void) {
    unsigned short nextWeight;
    unsigned short prevWeight;
    unsigned char spd = 0;
    unsigned short remaining = _TargetWeight - _FeederScale._Weight;

    // if we have not gotten a speed from the table yet, we start off at the last weight/speed entry in the table
    if (_LastWeightIndex == -1) {
        _LastWeightIndex = 20;
    }

    //unsigned short tabWeight = _FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b000011111111;

    // if we are at the first speed entry before raeaching the target weight, we can not go anywhere else
    if (_LastWeightIndex == 0) {
        return ((_FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b1111100000000000) >> 11);
    }

    // preload the next and previous set point weights to make things easier
    nextWeight = _FeederControlTable._ItemSpeedTable[_LastWeightIndex - 1] & 0b0000011111111111;
    prevWeight = _FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b0000011111111111;
    nextWeight *= 10;
    prevWeight *= 10;
    // weight needs to be under prevWeight and above the nextWeight (our preloaded weight set points)

    // we reached the next set point (we may have passed more than one.  start reading lower entries until we find one we are not under
    while (remaining < nextWeight) {

        // we are under the weight of the next set point so decrease the index of our table
         _LastWeightIndex--;
         // if we can't go any lower then index 0 so just return with the lowest weight speed
         if (_LastWeightIndex == 0) return ((_FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b1111100000000000) >> 11);

         // and just keep on checking lower weight points until we are not below the NEXT weight setpoint
         nextWeight = _FeederControlTable._ItemSpeedTable[_LastWeightIndex - 1] & 0b0000011111111111;
         nextWeight *= 10;
    }

    // if we are above the weight
    // in case we gained weight, go back up the table  (we should not really need this but we will add it anyway)
    while (remaining > prevWeight) {

        // can't go any faster so just return last entry to our table
        if (_LastWeightIndex == 21) return ((_FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b1111100000000000) >> 11);

        _LastWeightIndex++;
        prevWeight = _FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b0000011111111111;
        prevWeight *= 10;
    }

    // now return the speed for this index

    spd = (_FeederControlTable._ItemSpeedTable[_LastWeightIndex] & 0b1111100000000000) >> 11;
    return spd;
}



// saves the contents of the current weight/speed table and descriptor to the given index
void Save_WeightSpeedTableEntry(unsigned char index) {

    // First erase the block (we assume we have the data we want to write sitting in ram)

    // compute the address of the block we need to erase
    unsigned short addr = (SPEED_TABLE_HIGH_ADDRESS << 8) | SPEED_TABLE_LOW_ADDRESS;
    addr += (index * 64);

    Flash_Write_Block(addr, (char *)&_FeederControlTable);
}


// function to reinitialize or build the weight/speed mapping table
void Make_WeightSpeedEntries(void) {
    int i = 0;
    int c = 0;
    unsigned char speed = 0;
    unsigned short weight = 0;
    unsigned short weightCombo = 0x0000;

    strcpypgm2ram(_FeederControlTable._ItemDescStr, (rom far char*)"Item 1 Name        ");
    _FeederControlTable._ItemDescStr[19] = 0x00;

    speed = 5;
    weight = 5;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 6;
    weight = 8;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 7;
    weight = 20;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 8;
    weight = 85;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 9;
    weight = 100;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;


    speed = 10;
    weight = 140;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 10;
    weight = 200;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 10;
    weight = 300;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 10;
    weight = 500;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 10;
    weight = 600;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

       for (i = c; i < 22; i++) {
        speed = 10;
        weight = 600;
        weightCombo = (speed << 11) | weight;
        _FeederControlTable._ItemSpeedTable[i] = weightCombo;
    }

     Save_WeightSpeedTableEntry(0);

     c=0;
    strcpypgm2ram(_FeederControlTable._ItemDescStr, (rom far char*)"Item 2 Name        ");
    _FeederControlTable._ItemDescStr[19] = 0x00;

    speed = 6;
    weight = 5;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 7;
    weight = 10;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 8;
    weight = 30;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 9;
    weight = 85;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 11;
    weight = 100;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;


    speed = 12;
    weight = 140;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 13;
    weight = 200;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 14;
    weight = 300;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 15;
    weight = 500;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 16;
    weight = 600;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

       for (i = c; i < 22; i++) {
        speed = 16;
        weight = 600;
        weightCombo = (speed << 11) | weight;
        _FeederControlTable._ItemSpeedTable[i] = weightCombo;
    }

     Save_WeightSpeedTableEntry(1);



     c=0;
    strcpypgm2ram(_FeederControlTable._ItemDescStr, (rom far char*)"Item 3 Name        ");
    _FeederControlTable._ItemDescStr[19] = 0x00;

    speed = 8;
    weight = 5;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 9;
    weight = 10;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 10;
    weight = 30;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 11;
    weight = 85;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 12;
    weight = 100;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;


    speed = 13;
    weight = 140;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 14;
    weight = 200;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 15;
    weight = 300;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 16;
    weight = 500;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

    speed = 16;
    weight = 600;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[c] = weightCombo;
    c++;

       for (i = c; i < 22; i++) {
        speed = 16;
        weight = 600;
        weightCombo = (speed << 11) | weight;
        _FeederControlTable._ItemSpeedTable[i] = weightCombo;
    }

     Save_WeightSpeedTableEntry(2);



   strcpypgm2ram(_FeederControlTable._ItemDescStr, (rom far char*)"Item 4 Name         ");
    _FeederControlTable._ItemDescStr[19] = 0x00;

    speed = 7;
    weight = 40;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[0] = weightCombo;

    speed = 9;
    weight = 200;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[1] = weightCombo;

    speed = 12;
    weight = 400;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[2] = weightCombo;

    speed = 15;
    weight = 800;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[3] = weightCombo;

     speed = 16;
    weight = 1600;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[4] = weightCombo;

    speed = 16;
    weight = 3000;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[5] = weightCombo;

    speed = 16;
    weight = 5000;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[6] = weightCombo;

    speed = 16;
    weight = 6000;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[7] = weightCombo;

    speed = 16;
    weight = 7500;
    weightCombo = (speed << 11) | weight;
    _FeederControlTable._ItemSpeedTable[8] = weightCombo;

       for (i = 9; i < 22; i++) {
        speed = 16;
        weight = 7500;
        weightCombo = (speed << 11) | weight;
        _FeederControlTable._ItemSpeedTable[i] = weightCombo;
       }
    Save_WeightSpeedTableEntry(3);
}
