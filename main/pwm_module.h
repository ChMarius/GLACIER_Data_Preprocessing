#pragma once
#include <Arduino.h>

class PWMmodule {
public:
    PWMmodule(int pin, int channel, int freq, int resolution);
    void begin();
    void setDuty(float percentage); // 0.0 – 100.0
    void stop();

private:
    int _pin, _channel, _freq, _resolution;
};