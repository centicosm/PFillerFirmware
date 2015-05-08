/* 
 * File:   PDelay.h
 * Author: pulam
 *
 * Various custom delay routines to get around mplab limitations
 */

#ifndef PDELAY_H
#define	PDELAY_H

void Delay_10x_ms(unsigned char msx10);
void Delay_ms(unsigned char x);
void Delay_us(unsigned char x);
void Delay_5x_us(unsigned char x);

#endif	/* PDELAY_H */

