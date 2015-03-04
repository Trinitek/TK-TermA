
#include <xc.h>

void isr_keyboard(void) {
    //
}

void keyboardRead(void) {
    //
}

void keyboardSend(void) {
    //
}

void initKeyboard(void) {
    /*
     * The timer generates an interrupt everytime the counter overflows.
     * An 8-bit counter is chosen, which acts to scale the 16 MHz oscillator
     * frequency down to a ratio of 1:256. A prescale value of 1:8 means that
     * the counter is only incremented on the eighth oscillator cycle,
     * effectively scaling the oscillator frequency down to a ratio of 1:1024,
     * thus producing a frequency of 15.625 kHz, which is suitable for use as
     * the PS/2 data clock.
     */

    // setup timer 0 for driving clock signal on keyboard writes
    T0CONbits.T08BIT = 1;       // 8-bit counter
    T0CONbits.T0CS = 0;         // use internal 16 MHz clock
    T0CONbits.PSA = 0;          // prescaler enabled
    T0CONbits.T0PS = 0b010;     // prescale by 1:8
    INTCONbits.TMR0IE = 1;      // enable interrupt on overflow
    INTCONbits.TMR0IF = 0;      // clear the overflow flag
}
