/* 
 * File:   P_RS232.h
 * Author: pulam
 *
 * RS-232 serial communications library
 */

#ifndef PSERIAL_RS232_H
#define	PSERIAL_RS232_H

#include "PCircularBuffer.h"
#include "PSerial_RS232_Settings.h"
#include "PFiller_Globals.h"

#define PSERIAL_SW_FLOW_CONTROL
#define PSERIAL_XON          0x11
#define PSERIAL_XOFF         0x13


// Macros to disable/enable the tx inturrupt.  We will want to set this when we have data we want to send, disable otherwise
#define Flag_Tx()       PIE1bits.TXIE = true
#define Unflag_Tx()     PIE1bits.TXIE = false

// buffer size for the serial comms
#define RS232_RX_BUF_SIZE       16
#define RS232_TX_BUF_SIZE       2

extern unsigned char _RxBuf[RS232_RX_BUF_SIZE];
extern unsigned char _TxBuf[RS232_TX_BUF_SIZE];


#define RS232_TX_OVERFLOW               0b00000001
#define RS232_RX_OVERFLOW               0b00000010
#define RS232_TX_EMPTY                  0b00000100
#define RS232_HOLD_TRANSMIT             0b00001000


extern unsigned char _RS232_Flags;

void Init_RS232(void);

// write a byte to the serial port
//bool Write_Byte_RS232(char byte);

//  write a series of bytes to the serial port
//bool Write_Bytes_RS232(unsigned char *buf, unsigned char size);

// write a null terminated string to the serial port
//bool Write_String_RS232(unsigned char *str);

//bool Read_Byte_RS232(unsigned char *byte);

//void Transmit_Byte_RS232(void);

//void Add_Byte_To_ReadBuf_RS232(unsigned char byte);


#endif	/* PSERIAL_RS232_H */

