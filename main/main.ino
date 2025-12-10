#include "adc.h"
#include "pwm_module.h"
#include "NDIR_sensor.h"
#include "thermistor.h"
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

Adafruit_ADS1115 ads1115;
uint8_t adc_pin = 4;
float gas_concentration;
uint8_t cal_cons = 1; // calibration constant (idk if it will be changed in the later stages or should I make function for calculating it)

PWMmodule pwm_heater(25, 0, 5000, 10); // PWM setup for the MOSFAT heater: GPIO25, Channel 0, 5 khZ = 5000 Hz,  10-bit
PWMmodule pwm_NDIR(26, 1, 4000, 10); 
float NDIR_active_voltage, NDIR_ref_voltage, VQ5_differential_voltage;
float csp_voltage = 0; // Current sensor pump 

void setup() {
  // put your setup code here, to run once:
  pinMode(14, OUTPUT);
  Serial.begin(115200);
  Serial.println("It works.");
  pwm_heater.begin();
  pwm_NDIR.begin();
  Wire.begin(21, 22); // SDA -> 21, SCL -> 22
  ads1115.begin(); // External ADC setup

  pwm_NDIR.setDuty(30); // needs to be decided
  pwm_heater.setDuty(30); // needs to be decided
}

void loop() {
  // The temperature sensors will go on every 20s (not sure, could be changed), the gas sensors will go on immediately one after another

  // Current Sensor Pump logic
  float csp_voltage_raw = readADC(32);
  csp_voltage = csp_voltage_raw * 0.1875e-3;
  check_voltage_threshold(csp_voltage);

  // NDIR gas sensor logic
  float NDIR_raw_active_reading = ads1115.readADC_SingleEnded(0);
  float NDIR_raw_ref_reading = ads1115.readADC_SingleEnded(1);
  NDIR_active_voltage = NDIR_raw_active_reading * 0.1875e-3;
  NDIR_ref_voltage = NDIR_raw_ref_reading * 0.1875e-3;
  gas_concentration = NDIR_gas_reading(NDIR_active_voltage, NDIR_reference_voltage, cal_cons);

  // NDIR temp sensor
  float NDIR_temp_voltage = ads1115.readADC_SingleEnded(3);


  // thermistors
  int16_t voltage = readADC(34);
  float resistance_ntc = calculate_resistance(voltage);
  float temperature_th_heater = calculate_temperature(resistance_ntc);

  voltage = readADC(35);
  resistance_ntc = calculate_resistance(voltage);
  float temperature_th_sensor = calculate_temperature(resistance_ntc);
  /// I2C Logic
  //
  // Digital values from the external ADC will go through the I2C for PLC and OLED implementation
  //
  ////// 

  //// PLC alarm Logic
  //
  // Input parameters: gas digital values, Output parameters: 10V signal to the PLC
  //
  ///////

  ///// OLED logic
  //
  // Input parameters: gas digital values, Output: numbers on screen
  //
  /////
}
