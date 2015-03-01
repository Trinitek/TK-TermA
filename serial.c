
#include <xc.h>

void initSerial(void) {
    // setup transmission
    TXSTAbits.TX9 = 0;          // 8-bit transmission
    TXSTAbits.TXEN = 1;         // enable transmission
    TXSTAbits.SYNC = 0;         // asynchronous
    TXSTAbits.BRGH = 0;         // low speed baud rate

    // setup reception
    RCSTAbits.SPEN = 1;         // enable serial port
    RCSTAbits.RX9 = 0;          // 8-bit reception
    RCSTAbits.CREN = 1;         // continuously receive data

    // setup baud generator
    BAUDCONbits.SCKP = 0;       // do not invert data on transmission
    BAUDCONbits.BRG16 = 0;      // use 8-bit generator
    BAUDCONbits.ABDEN = 0;      // disable baud detect
    SPBRG1 = 51;                // 2400 baud at 8 MHz
    SPBRGH1 = 0;
}

void initPS2(void) {
    //
}