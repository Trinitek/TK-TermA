
#include <stdbool.h>
#include "system.h"
#include "serial.h"

void main(void) {

    initOscillator();
    initPorts();
    initSerial();

    char hello[] = "Hello world!";
    sendString(hello);

    while (true) {
        //
    }
}
