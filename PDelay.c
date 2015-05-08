#include <delays.h>
#include "PFiller_Globals.h"



// 0 - 127 are the onlu valid values
void Delay_5x_us(unsigned char x) {
    Delay10TCYx(x >> 2);
}

void Delay_ms(unsigned char x) {
    unsigned char i;

    for (i = 0; i < x; i++) {
        Delay1KTCYx(4);
    }
}


void Delay_10x_ms(unsigned char msx10) {
    unsigned char i;
    for (i = 0; i < msx10; i++) {
         Delay_ms(10);
    }
}


