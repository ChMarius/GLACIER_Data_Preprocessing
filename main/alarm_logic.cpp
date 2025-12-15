#include <Arduino.h>
#include "alarm_logic.h"

// Alarm threshold definition
// Value represents gas concentration (e.g. 0.03 = 3%)
float GAS_ALARM_THRESHOLD = 0.03f;

// GPIO pin driving relay / optocoupler
static const uint8_t PLC_ALARM_PIN = 13;

// Tracks current alarm state to avoid redundant GPIO toggling
static bool alarmActive = false;

void initAlarmOutput()
{
    // Configure alarm pin as output
    pinMode(PLC_ALARM_PIN, OUTPUT);

    // Default state: alarm OFF
    // Assumes LOW = relay inactive
    digitalWrite(PLC_ALARM_PIN, LOW);

    alarmActive = false;
}

void checkLimitForAlarm(float gas_value)
{
    // Trigger alarm when threshold is exceeded
    if (gas_value >= GAS_ALARM_THRESHOLD && !alarmActive)
    {
        sendSignalToPLC(true);
        alarmActive = true;
    }
    // Clear alarm when value drops below threshold
    else if (gas_value < GAS_ALARM_THRESHOLD && alarmActive)
    {
        sendSignalToPLC(false);
        alarmActive = false;
    }
}

void sendSignalToPLC(bool activate)
{
    // This assumes the relay module is active-HIGH
    // If the relay is active-LOW, logic MUST be inverted
    digitalWrite(PLC_ALARM_PIN, activate ? HIGH : LOW);
}

bool isAlarmActive()
{
    // Returns internal software state
    return alarmActive;
}
