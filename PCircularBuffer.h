/* 
 * File:   PCircularBuffer.h
 * Author: pulam
 *
 * Created on January 31, 2013, 2:07 PM
 */

#ifndef PCIRCULARBUFFER_H
#define	PCIRCULARBUFFER_H


#include "stdbool.h"

#define LAST_CIRC_BUF_OP_WRITE               0b10000000

// Bookkeeping information related to the circular bufferss
typedef struct {
    unsigned char _Size;                            // the MSB of size serves as the last operation indicator
    unsigned char _ReadPos;
    unsigned char _WritePos;
    unsigned char *_Buf;
} CircularBufHeader;


//#define CBuffer(bname, x) union { CircularBufHeader _Header; struct { CircularBufHeader _Header; unsigned char _Buf[x - 1]; } _Buffer; } bname;
//#define CBuffer(bname, x) union { CircularBufHeader _Header; struct { CircularBufHeader _Header; unsigned char _Buf[x - 1]; } _Buffer; } bname;


void Init_CircularBuffer(CircularBufHeader *buf, unsigned char bufSize);
bool Is_Empty(CircularBufHeader *buf);
bool Add_ByteToCircBuf(CircularBufHeader *buf, char byte);
//bool Add_ByteToCircBuf(char bye, char t);
bool Read_ByteFromCircBuf(CircularBufHeader *buf, unsigned char *byte);


#endif	/* PCIRCULARBUFFER_H */
