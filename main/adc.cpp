#include <Arduino.h>
#include "adc.h"

float readADC(int pin) {
    int raw = analogRead(pin);
    return (raw / 4095.0) * 3.3;
}