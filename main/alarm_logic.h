#pragma once

#include <Arduino.h>

// Gas concentration threshold (e.g. 0.03 = 3%)
extern float GAS_ALARM_THRESHOLD;

// Initialize PLC alarm output pin
void initAlarmOutput();

// Check gas value and update alarm state
void checkLimitForAlarm(float gas_value);

// Manually control PLC alarm relay
void sendSignalToPLC(bool activate);

// Read current alarm state
bool isAlarmActive();
