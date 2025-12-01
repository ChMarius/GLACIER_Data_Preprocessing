#include "adc.h"

uint8_t pin_adc = 4;

float readADC(int pin) {
    int raw = analogRead(pin);
    return (raw / 4095.0) * 3.3;
}