/* 
 * File:   PLib_Defines.h
 * Author: pulam
 *
 * Created on February 5, 2013, 2:08 PM
 */

#ifndef PLIB_DEFINES_H
#define	PLIB_DEFINES_H

#define OUTPUT_TRIS         0
#define INPUT_TRIS          1

#define LOW_BYTE(x)     ((unsigned char)((x)&0xFF))
#define HIGH_BYTE(x)    ((unsigned char)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((unsigned short)((x)&0xFFFF))
#define HIGH_WORD(x)    ((unsigned short)(((x)>>16)&0xFFFF))

#endif	/* PLIB_DEFINES_H */

