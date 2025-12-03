#include "pwm_module.h"

PWMmodule::PWMmodule(int pin, int channel, int freq, int resolution)
: _pin(pin), _channel(channel), _freq(freq), _resolution(resolution) {}

void PWMmodule::begin() {
    ledcSetup(_channel, _freq, _resolution);
    ledcAttachPin(_pin, _channel);
}

void PWMmodule::setDuty(float percent) {
    percent = constrain(percent, 0.0f, 100.0f);
    int maxDuty = (1 << _resolution) - 1;
    int duty = (percent / 100.0f) * maxDuty;
    ledcWrite(_channel, duty);
}

void PWMmodule::stop() {
    ledcWrite(_channel, 0);
}