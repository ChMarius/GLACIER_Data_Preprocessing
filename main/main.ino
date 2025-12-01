#include "adc.h"
#include <Adafruit_ADS1X15.h>

uint8_t adc_pin = 4;

Adafruit_ADS1015 ads1015;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  float digital_value = readADC(adc_pin);

}
