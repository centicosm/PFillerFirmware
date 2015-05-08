#include "stdbool.h"
#include "PApp_Config.h"
#include "PFlash.h"


// delete the data at the given address in flash
void Flash_Erase_Block(unsigned int deleteAddr) {

     // First erase the block (we assume we have the data we want to write sitting in ram)

    TBLPTRU = 0x00;
    TBLPTRH = (deleteAddr & 0xFF00) >> 8;
    TBLPTRL = (deleteAddr & 0x00FF);

    EECON1bits.EEPGD = true;            // point to program memory
    EECON1bits.CFGS = false;            // we are not accessing config memory
    EECON1bits.WREN = true;             // enable writes
    EECON1bits.FREE = true;             // perform an erase

    INTCONbits.GIE = false;             // Global interrupts off

    EECON2 = 0x55;                      // send the secret code
    EECON2 = 0x0AA;

    EECON1bits.WR = true;               // start the erase

    _asm
        TBLRDPOSTDEC
    _endasm

    INTCONbits.GIE = true;              // interrupts back on

}



// write the contents of the given buffer to the given address.  It is assumed that the buffer contains enough data to supply
//     the necessary block write
void Flash_Write_Block(unsigned int addr, char *buf) {
    unsigned char i;

        TBLPTRU = 0x00;
    TBLPTRH = (addr & 0xFF00) >> 8;
    TBLPTRL = (addr & 0x00FF);

    EECON1bits.EEPGD = true;            // point to program memory
    EECON1bits.CFGS = false;            // we are not accessing config memory
    EECON1bits.WREN = true;             // enable writes
    EECON1bits.FREE = true;             // perform an erase

    INTCONbits.GIE = false;             // Global interrupts off

    EECON2 = 0x55;                      // send the secret code
    EECON2 = 0x0AA;

    EECON1bits.WR = true;               // start the erase

    _asm
        TBLRDPOSTDEC
    _endasm

    INTCONbits.GIE = true;              // interrupts back on

    // Write the block to the holding register
    for (i = 0; i < FLASH_BLOCK_SIZE; i++) {
        _asm
            TBLWTPOSTINC 
        _endasm
       TABLAT = buf[i];
    }

    EECON1bits.EEPGD = true;            // write to program memory
    EECON1bits.CFGS = false;            // we are not accessing config memory
    EECON1bits.WREN = true;             // enable writes
    
    INTCONbits.GIE = false;             // Global interrupts off

    EECON2 = 0x55;                      // send the secret code
    EECON2 = 0x0AA;

    EECON1bits.WR = true;               // start the write

    INTCONbits.GIE = true;              // write is done so turn interrupts back on
    EECON1bits.WREN = false;             // enable writes
}



// read numBytes from program memory and store it in the given buffer
void Flash_Read(unsigned int addr, char *buf, unsigned char numBytes) {
    unsigned char i;
    
    // set the table pointer to point to the correct address in flash
    TBLPTRU = 0x00;
    TBLPTRH = (addr & 0xFF00) >> 8;
    TBLPTRL = (addr & 0x00FF);

    // read the specified number of bytes into our buffer
    for (i = 0; i < numBytes; i++) {
        _asm
            TBLRDPOSTINC
        _endasm
       buf[i] = TABLAT;
    }
}


