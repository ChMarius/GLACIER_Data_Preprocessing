#include "adc.h"
#include "pwm_module.h"
#include "alarm_logic.h"
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

uint8_t adc_pin = 4;
float digital_value;

Adafruit_ADS1015 ads1015;
PWMmodule pwm(25, 0, 5000, 10);

void setup() {
  Serial.begin(115200)
  Wire.begin(21, 22) // SDA -> 21, SCL -> 22
  ads1015.begin(); // External ADC setup
  pwm.begin()
  // put your setup code here, to run once:
  initAlarmOutput(); 
}

void loop() {
   ////////// Sensor reading logic + PWM
   //
   // The temperature sensors va will go on every 20s (not sure, could be changed), the gas sensors will go on immediately one after another
   //
   /////////

  // ADC logic - external ADC will convert the NDIR, sensor 2, temperature sensor 1, internal ADC will convert the last two temperature sensors
  //if(NDIR & S2 & T1)
    digital_value = ads1015.readADC_SingleEnded(0);
  //else
    float digital_value = readADC(adc_pin);

  /// I2C Logic
  //
  // Digital values from the external ADC will go through the I2C for PLC and OLED implementation
  //
  ////// 

  //// PLC alarm Logic
  //
  // Input parameters: gas digital values, Output parameters: 10V signal to the PLC
  //
    checkLimitForAlarm(digital_value);
  

  ///// OLED logic
  //
  // Input parameters: gas digital values, Output: numbers on screen
  //
  /////
}
