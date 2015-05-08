#include <p18f25k50.h>
#include "PFiller_Globals.h"

unsigned char _RS232_Flags = 0x00;
//union { CircularBufHeader _Header; struct { CircularBufHeader _Header; unsigned char _Buf[RS232_RX_BUF_SIZE]; } _Buffer; } _RxBuf;
//union { CircularBufHeader _Header; struct { CircularBufHeader _Header; unsigned char _Buf[RS232_TX_BUF_SIZE]; } _Buffer; } _TxBuf;

unsigned char _RxBuf[RS232_RX_BUF_SIZE] = {0};
unsigned char _TxBuf[RS232_TX_BUF_SIZE] = {0};



// Initialize the serial port for communication at the given baudrate
void Init_RS232(void) {
    unsigned short baudGen;

    // prepeare the transmit and receive buffers
  //  Init_CircularBuffer((CircularBufHeader *)&_RxBuf, RS232_RX_BUF_SIZE);
  //  Init_CircularBuffer((CircularBufHeader *)&_TxBuf, RS232_TX_BUF_SIZE);

    _RS232_Flags |= RS232_TX_EMPTY;

    // determine the baud rate scaler
    baudGen = ((SYS_FREQ / 4) / RS232_BAUD_RATE) + 1;

    TXSTA1 = 0;                                  // clear the rx and tx control ports
    RCSTA1 = 0;

    //  Set up the baud rate
    TXSTA1bits.BRGH  = 1;                        // we are going to always use the high speed, high resolution baud generator.
    BAUDCON1bits.BRG16 = 1;                      //       Why not?  Uses more power?
    SPBRG1 = LOW_BYTE(baudGen);
    SPBRGH1 = HIGH_BYTE(baudGen);

    ANSELCbits.ANSC6 = false;                                     // set all outputs on port C are digital
    ANSELCbits.ANSC7 = false;                                     // set all outputs on port C are digital

    TRISCbits.RC6 = INPUT_TRIS;;                             // Set up pins for serial usage (Rx = 7, Tx = 6)
    TRISCbits.RC7 = INPUT_TRIS;

    TXSTA1bits.SYNC = false;
    RCSTA1bits.SPEN = true;                            // Enable serial transmission and reception
    TXSTA1bits.TXEN = true;

    // Generate interrupt when data is received (rx)

    PIE1bits.RCIE = 1;

    RCSTA1bits.CREN = true;    // enable the reciever
}


// write a byte to the serrial port
/*
bool Write_Byte_RS232(char byte) {


 //   if (!Add_ByteToCircBuf(&_TxBuf._Header, byte)) {
 //       _RS232_Flags |= RS232_TX_OVERFLOW;
 //       return false;
  //  }

    Flag_Tx();                                  // When the USART is free to send data, trigger and interrupt
    
    return true;
}


//  write a series of bytes to the serial port
bool Write_Bytes_RS232(unsigned char *buf, unsigned char size) {
    unsigned char i;
    for (i = 0; i < size; i++) {
        if (!Add_ByteToCircBuf(&_TxBuf._Header, buf[i])) {
            _RS232_Flags |= RS232_TX_OVERFLOW;
            return false;
        }

        // TODO - Make sure this is not a problem.  We could still be and likely will) be filling up the data when the interrupt goes off
        Flag_Tx();                                  // When the USART is free to send data, trigger and interrupt
    }
     
    return true;
}

// write a null terminated string to the serial port
bool Write_String_RS232(unsigned char *str)  {
 
    int i = 0;
    while (str[0]) {
        if (!Add_ByteToCircBuf( &_TxBuf._Header, str[i])) {
            _RS232_Flags |= RS232_TX_OVERFLOW;
            return false;
        }

        // TODO - Make sure this is not a problem.  We could still be and likely will be filling up the data when the interrupt goes off
        Flag_Tx();                                  // When the USART is free to send data, trigger and interrupt
        i++;
    }

    return true;
}


bool Read_Byte_RS232(unsigned char *byte) {
    bool res = Read_ByteFromCircBuf(&(_RxBuf._Header), byte);
    return res;

}

void Add_Byte_To_ReadBuf_RS232(unsigned char byte) {
    if (Add_ByteToCircBuf(&(_RxBuf._Header), byte) == false) {
        _RS232_Flags |= RS232_RX_OVERFLOW;
    }
}

void Transmit_Byte_RS232(void) {
    unsigned char byte;
    if (Read_ByteFromCircBuf(&(_TxBuf._Header), &byte) == true) {

        // and put it byte into the transmit register
        TXREG = byte;
    }
    else {

        // if there are no more bytes to transmit, turn off the interrupt
        _RS232_Flags |= RS232_TX_EMPTY;
        Unflag_Tx();
    }
}
*/