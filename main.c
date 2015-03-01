
#include <stdbool.h>
#include "system.h"
#include "serial.h"
#include "lcd.h"

void main(void) {

    initOscillator();
    initPorts();
    initSerial();
    initLcd();

    while (true) {
        //
    }
}
