
#include <xc.h>
#include <stdbool.h>

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

/**
 * Send an 8-bit character over RS-232 if the transmit shift register is empty
 * @param character
 * @return true if successful
 */
bool sendSerial(char c) {
    if (TXSTAbits.TRMT) {
        TXREG = c;
        return true;
    } else {
        return false;
    }
}

/**
 * Force send an 8-bit character over RS-232
 * @param character
 */
void sendChar(char c) {
    while (!sendSerial(c));
}

/**
 * Send a string of 8-bit characters over RS-232
 * @param string - array of characters
 */
void sendString(char string[]) {
    int i = 0;
    while(string[i] != 0) {
        sendChar(string[i]);
        i++;
    }
}

/**
 * Get a character sent over RS-232 that is waiting in the receiver FIFO
 * @return character
 */
char getSerial(void) {
    // If a byte was not received, return 0
    if (PIR1bits.RC1IF) return RCREG;
    else return 0;
}
