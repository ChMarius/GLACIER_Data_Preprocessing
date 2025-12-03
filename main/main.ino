#include "adc.h"
#include "pwm_module.h"
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

uint8_t adc_pin = 4;
float digital_value;

Adafruit_ADS1015 ads1015;
PWMmodule pwm(25, 0, 5000, 10);

void setup() {
  Serial.begin(115200)
  Wire.begin(21, 22) // SDA -> 21, SCL -> 22
  ads1015.begin();
  pwm.begin()
  // put your setup code here, to run once:

}

void loop() {
  //if(NDIR & S2 & T1)
    digital_value = ads1015.readADC_SingleEnded(0);
  //else
    float digital_value = readADC(adc_pin);

}
