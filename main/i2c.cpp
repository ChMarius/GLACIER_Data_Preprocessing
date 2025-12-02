#include <Arduino.h>
#include <Wire.h>

void scanI2Cbus()
{
  Serial.println("Scanning I2C bus...");
  
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");
      Serial.println(address, HEX);
    }
  }
  
  Serial.println("Scan complete.");
}