/* 
 Basic routines for reading to and writing from the on chip flash memory
 */

#ifndef PFLASH_H
#define	PFLASH_H

void Flash_Erase_Block(unsigned int addr);
void Flash_Read(unsigned int addr, char *buf, unsigned char numBytes);
void Flash_Write_Block(unsigned int addr, char *buf);


#endif	/* PFLASH_H */

