#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads1115;

float NDIR_gas_reading(float active_voltage, float reference_voltage, float cal_cons)
{
  float concentration = 0;
  float transmission = active_voltage / (reference_voltage + 0.000001);

  float absorbance = -log(transmission);
  return concentration = cal_cons * absorbance;
}

// Function used for averaging values (both for the NDIR sensor and the catalytic one)
float multi_sample_averaging(uint8_t channel, uint8_t sensor, uint16_t raw_reading)
{
  long sum = 0;
   for(uint8_t i = 0; i < 20; i++)
   {
     if(sensor==0){
        sum += ads1115.readADC_SingleEnded(channel);
     }
     else {
        sum += ads1115.readADC_Differential_2_3();
     }
     delayMicroseconds(100);
   }
  float average_raw = (float)sum / 20;
  return average_raw * 0.1875e-3;  // convert to volts
}

