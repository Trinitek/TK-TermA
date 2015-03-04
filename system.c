
#include <xc.h>

void initOscillator(void) {
    OSCCONbits.IRCF = 0b111;    // 16 MHz
}

void initPorts(void) {
    // disable all analog functionality
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
}

#pragma interrupt isr

void isr(void) {
    //
}

#pragma code
