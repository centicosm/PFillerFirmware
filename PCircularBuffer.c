#include "PCircularBuffer.h"


// Initialize the bookkeeping info for a new circular buffer
void Init_CircularBuffer(CircularBufHeader *buf, unsigned char bufSize)  {
    buf->_Size = bufSize;
    buf->_ReadPos = 0;
    buf->_WritePos = 0;
}

bool Is_CircBufEmpty(CircularBufHeader *buf) {
    if ((buf->_ReadPos == buf->_WritePos) && (buf->_Size  & LAST_CIRC_BUF_OP_WRITE)) return true;
    return false;
}


// Add a byte to the circular buffer
bool Add_ByteToCircBuf(CircularBufHeader *buf, char byte) {
    unsigned char unmaskedSize;
    // check for a full buffer : if the last op was a right and we are on the same index as the
    //    read index, that means we looped
    if ((buf->_ReadPos == buf->_WritePos) && (buf->_Size & LAST_CIRC_BUF_OP_WRITE)) return false;

    buf->_Buf[buf->_WritePos] = byte;
    buf->_WritePos++;

    // remove the last operation bit from the size so we can check for wrap around
    unmaskedSize = buf->_Size & ~LAST_CIRC_BUF_OP_WRITE;

    // wrap around the buffer if we reached the end
    if (buf->_WritePos == unmaskedSize)  {
        buf->_WritePos = 0;
    }

    // mark that the last operation was a write for overflow detection
    buf->_Size |= LAST_CIRC_BUF_OP_WRITE;

    return true;
}


bool Read_ByteFromCircBuf(CircularBufHeader *buf, unsigned char *byte) {
    unsigned char ccc;
    unsigned char unmaskedSize;
    // check for an empty buffer->  If the write and read pointer are equal, and the last op was a read
    //    then we read all the bytes from buffer
    if ((buf->_ReadPos == buf->_WritePos) && !(buf->_Size & LAST_CIRC_BUF_OP_WRITE)) return false;

//    ccc = buf->_Buf[buf->_ReadPos];
    *byte = buf->_Buf[buf->_ReadPos];

    buf->_ReadPos++;

    // remove the last operation bit from the size so we can check for wrap around
    unmaskedSize = buf->_Size & ~LAST_CIRC_BUF_OP_WRITE;

    // wrap around the buffer if we reached the end
    if (buf->_ReadPos == unmaskedSize)  {
        buf->_ReadPos = 0;
    }

    // and now we remove the high bit from size as the last  op was a read
    buf->_Size = unmaskedSize;

    return true;
}
