#include <Arduino.h>

void check_voltage_threshold(float csp_voltage)
{
  if (csp_voltage > 2){
    digitalWrite(14, HIGH);
    delay(500);
    digitalWrite(14, LOW);
    delay(500);
  }
}