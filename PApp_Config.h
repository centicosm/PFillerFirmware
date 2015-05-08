/* 
 * File:   PApp_Config.h
 *
 *   Contains general non-application specific but hardware specific defines necessary for certain libraries.
 *      This includes the flash block size and clock frequencies
 *      In addition, this contains various helper macros, defines, etc all of which are non-application specific
 */

#ifndef PAPP_CONFIG_H
#define	PAPP_CONFIG_H

#include <p18f25k50.h>

//  Clock parameters
#define SYS_FREQ                16000000L
#define FCY                     SYS_FREQ/4
#define _XTAL_FREQ              16000000L

// flash and eprom parameters
#define FLASH_BLOCK_SIZE        64

// helper macros
#define OUTPUT_TRIS             0
#define INPUT_TRIS              1

#define LOW_BYTE(x)     ((unsigned char)((x)&0xFF))
#define HIGH_BYTE(x)    ((unsigned char)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((unsigned short)((x)&0xFFFF))
#define HIGH_WORD(x)    ((unsigned short)(((x)>>16)&0xFFFF))


#endif	/* PAPP_CONFIG_H */

