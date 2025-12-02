#include "adc.h"
#include <Arduino.h>

float readADC(int pin) {
    int raw = analogRead(pin);
    return (raw / 4095.0) * 3.3;
}