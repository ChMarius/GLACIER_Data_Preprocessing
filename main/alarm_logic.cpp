//  The alarm system will take input parameters the values from gas sensors and for each values it should check if the values is above the limit. If it is, send a 10V signal to the PLC
//  and if not, exit the method, basicall return nothing and do nothing.
// void checkLimitForAlarm(float gas_value)
//       if (gas_value > limit)
//       {      
//          send_signal_to_PLC() //another function, specifically for sending the signal
//       } 
//
// There should be another function for sending signal to the PLC: send_signal_to_PLC()
// This is my train though and how I think the implementation should be, but of course, it remains to the choice of the programmer of this part.
#include "alarm_logic.h"
#include <Arduino.h>

// GPIO13 controls relay K1 - pin J2_15 on ESP32  -- correct me if i'm wrong
static const int PLC_ALARM_PIN = 13;

// Alarm threshold: Trigger at 3% gas concentration
float GAS_ALARM_THRESHOLD = 0.03f;

// Internal state tracking
static bool alarmActive = false;


//Initialize the alarm output system
//Sets up GPIO pin and ensures alarm starts in OFF state
void initAlarmOutput()
{
    pinMode(PLC_ALARM_PIN, OUTPUT);
    digitalWrite(PLC_ALARM_PIN, LOW); // Relay OFF → 0V to PLC
    alarmActive = false;
}


//Check if gas concentration exceeds limit and trigger alarm if needed
//@param gas_value: Current gas concentration (0.0 to 1.0 scale)
void checkLimitForAlarm(float gas_value)
{
    if (gas_value > GAS_ALARM_THRESHOLD) {
        // Above threshold: activate alarm (send 10V signal)
        send_signal_to_PLC(true);
    } else {
        // Below threshold: deactivate alarm (send 0V signal)
        send_signal_to_PLC(false);
    }
}


//Send alarm signal to PLC by controlling relay
//@param activate: true = relay ON (10V to PLC), false = relay OFF (0V to PLC)
void send_signal_to_PLC(bool activate)
{
    if (activate) {
        digitalWrite(PLC_ALARM_PIN, HIGH); // Energize relay → PLC sees 10V
        alarmActive = true;
    } else {
        digitalWrite(PLC_ALARM_PIN, LOW);  // De-energize relay → PLC sees 0V
        alarmActive = false;
    }
}


//Query current alarm state
//@return: true if alarm is currently active, false otherwise
bool isAlarmActive()
{
    return alarmActive;
}

