
#include <xc.h>
#include <stdbool.h>
#include "lcd.h"

/*
 * The LCD module is configured to work in 4-bit mode, where the module's data
 * pins DB4 through DB7 correspond to the microcontroller's pins RA0 through
 * RA3, respectively. This means that DB4 is the least significant bit, as is
 * RA0.
 *
 * Two read or write cycles are required to transmit a full byte. The most
 * significant nibble must be transerred first.
 *
 * Data is passed to and from these functions in the lower nibble of a full
 * 8-bit char type.
 */

#define RegSelect   LATAbits.LATA7
#define RWSelect    LATAbits.LATA6
#define Enable      LATAbits.LATA5
#define DB7         LATAbits.LATA0
#define DB6         LATAbits.LATA1
#define DB5         LATAbits.LATA2
#define DB4         LATAbits.LATA3

#define CTRL        false
#define DATA        true

void writeLcd(bool reg, char data) {
    RegSelect = reg;
    RWSelect = 0;
    Enable = 1;

    // top nibble first
    DB4 = (data & 16);
    DB5 = (data & 32);
    DB6 = (data & 64);
    DB7 = (data & 128);
    waitLcd();

    // bottom nibble second
    DB4 = (data & 1);
    DB5 = (data & 2);
    DB6 = (data & 4);
    DB7 = (data & 8);
    waitLcd();

    Enable = 0;
}

void waitLcd(void) {
    TMR2 = 0;               // clear timer 2
    PIR1bits.TMR2IF = 0;    // clear timer 2 match bit
    while (!PIR1bits.TMR2IF);
                            // loop until match bit is set again
}

void initLcd(void) {
    T2CONbits.T2OUTPS = 0;  // disable postscaler
    T2CONbits.T2CKPS = 2;   // set prescaler to 1:16
    T2CONbits.TMR2ON = 1;   // enable timer 2

    writeLcd(CTRL, 0x2C);   // 4-bit bus, 2 lines, 5x10 font (0b00101100)
    writeLcd(CTRL, 0x0F);   // display enabled, cursor enabled, cursor blinking
}
