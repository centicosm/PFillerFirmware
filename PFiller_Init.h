#ifndef PFILLER_INIT_H
#define PFILLER_INIT_H

// Declarations of the initialization routines which prepare all the periphrials and interrupts for operation


// LCD Related Pins

// RA0 - LCD-RS
// RA1 - LCD-R/W
// RA3 - LCD-E

// RA4 - LCD-D4
// RA5 - LCD-D5
// RA6 - LCD-D6
// RA7 - LCD-D7


// Serial Related Pins
// RC6  -  TX
// RC7  -  RX


// Feeder Control Pins
// RA2 - DACOUT
// RC0 - Chip select DACOUT buffer


void Init_Filler(void);             // core init routine, calls all other init functions
void Init_Oscillator(void);
void Init_LCD(void);                // set up the lcd
void Init_DAC(void);                // initialize the dac for communicating with the feeder controller
void Init_ButtonInterface(void);    //  Initialize the pins for all the buttons that will be used (foot, lcd up/down/select)

#endif