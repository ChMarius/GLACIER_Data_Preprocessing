#include <Wire.h>
#include <adc.h>
#include <math.h>

float A = 1.20359e-3;
float B = 1.98433e-4;
float C = 1.67412e-7;
float R_FIXED = 2200.0;
float VCC = 3.3;

float calculate_temperature(float resistance) 
{
  double ln_resistance = log(resistance);
  double inverse_temp = A + B * ln_resistance + C * (ln_resistance * ln_resistance * ln_resistance);
  double temperature_kelvin = 1.0 / inverse_temp;
  return temperature_kelvin - 273.15;
}

float calculate_resistance(float voltage)
{
  float resistance_ntc = R_FIXED * (voltage / (VCC - voltage));
  return resistance_ntc;
}