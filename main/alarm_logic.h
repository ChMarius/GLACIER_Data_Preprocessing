#pragma once

#include <Arduino.h>

// Alarm threshold configuration
extern float GAS_ALARM_THRESHOLD;  // Trigger at this gas concentration (0.03 = 3%)

static const int PLC_ALARM_PIN = 13;


//Initialize the alarm output system
//Sets up GPIO pin and ensures alarm starts in OFF state

void initAlarmOutput();


//Check if gas concentration exceeds limit and trigger alarm if needed
//@param gas_value: Current gas concentration from NDIR sensor

void checkLimitForAlarm(float gas_value);


//Send alarm signal to PLC by controlling relay
//@param activate: true = relay ON (10V to PLC), false = relay OFF (0V to PLC)

void send_signal_to_PLC(bool activate);


//Query current alarm state
//@return: true if alarm is currently active, false otherwise

bool isAlarmActive();
