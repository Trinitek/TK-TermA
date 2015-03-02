
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
#define DB7         LATAbits.LATA3
#define DB6         LATAbits.LATA2
#define DB5         LATAbits.LATA1
#define DB4         LATAbits.LATA0

#define CTRL        0
#define DATA        1

/**
 * Write a null terminated string array to the LCD.
 * @param string
 */
void print(char string[]) {
    int i = 0;
    char c;

    while (true) {
        c = string[i];
        if (!c) break;
        writeLcd(DATA, c);
        i++;
    }
}

void writeNibbleLcd(bool reg, char data) {
    RegSelect = reg;
    RWSelect = 0;

    // only write the bottom nibble of data
    DB4 = (data & 1);
    DB5 = (data & 2);
    DB6 = (data & 4);
    DB7 = (data & 8);
    Enable = 1;
    waitLcd();
    Enable = 0;
    waitLcd();
}

void writeLcd(bool reg, char data) {
    RegSelect = reg;
    RWSelect = 0;
    char temp = data >> 4;

    writeNibbleLcd(reg, temp);      // most significant nibble first
    writeNibbleLcd(reg, data);      // least significant nibble last
}

void waitLcd(void) {
    TMR2 = 0;                       // clear timer 2
    PIR1bits.TMR2IF = 0;            // clear timer 2 match bit
    while (!PIR1bits.TMR2IF);
                                    // loop until match bit is set again
}

void initLcd(void) {
    T2CONbits.T2OUTPS = 0;          // disable postscaler
    T2CONbits.T2CKPS = 2;           // set prescaler to 1:16
    T2CONbits.TMR2ON = 1;           // enable timer 2

    waitLcd();                      // allow the LCD to initialize

    // perform a software reset of the LCD
    for (int i = 0; i < 3; i++) {
        writeNibbleLcd(CTRL, 0b00000011);
    }

    writeNibbleLcd(CTRL, 0b00000010);   // set to 4-bit operation

    writeLcd(CTRL, 0b00101000);     // 4-bit, 2 lines, 5x8 font
    writeLcd(CTRL, 0b00001111);     // display on, underline cursor, block cursor
    writeLcd(CTRL, 0b00000001);     // clear display
    writeLcd(CTRL, 0b00000110);     // address counter increments, no display shift
    writeLcd(DATA, 'W');
}
