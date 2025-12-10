#pragma once

#include <Arduino.h>

// Alarm threshold configuration
extern float GAS_ALARM_THRESHOLD;  // Trigger at this gas concentration (0.03 = 3%)

// Initialize alarm output on GPIO13 (relay control)
void initAlarmOutput();

// Check gas concentration and control relay alarm
// @param gas_value: Gas concentration (0.0 to 1.0 scale)
void checkLimitForAlarm(float gas_value);

// Send alarm signal to PLC via relay
// @param activate: true = relay ON (10V to PLC), false = relay OFF (0V to PLC)
void send_signal_to_PLC(bool activate);

// Query current alarm state
// @return: true if alarm is active, false otherwise
bool isAlarmActive();
