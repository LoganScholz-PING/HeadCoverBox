#include "ServoMotorControl.h"
#include <NewTone.h>

extern boolean motor_moving; // from main.cpp

/* === START SERVO MOTOR VARIABLE DEFINITIONS === */
boolean _motor_enable = false;
boolean _motor_direction = MOTOR_CCW;
 
unsigned long _max_freq = 35000;
float _current_speed = 0;

void servoMotorSetup()
{
    pinMode(mtrPulsePin, OUTPUT);
    pinMode(mtrDirectionPin, OUTPUT);
    pinMode(mtrEnablePin, OUTPUT);

    digitalWrite(mtrEnablePin, MOTOR_DISABLED);
    digitalWrite(mtrDirectionPin, MOTOR_CCW);
}

void servoMotorEnable(byte v)
{
    // Toggle state of the mtrEnablePin
    digitalWrite(mtrEnablePin, v);
    _motor_enable = (v == 0);
    if (_motor_enable == false)
    {
        // Turn off the PWM to the motor
        // When Motor is disabled
        noNewTone(mtrPulsePin);
        motor_moving = false;
    }
}

void servoMotorFrequency(float f)
{
    if ( f < 0 ) { f = 0; }
    if ( f > 1.0 ) { f = 1.0; }

    _current_speed = f;
    // use f to determine speed relative to
    // max frequency
    unsigned long x = (f * _max_freq);

    // NewTone(pin, freq, length)
    // if length not present, it lasts forever
    NewTone(mtrPulsePin, x);
}

void servoMotorDirection(boolean v)
{
    _motor_direction = v;
    digitalWrite(mtrDirectionPin, _motor_direction);
}

void runMotor(int cmd, float f)
{
  if (cmd == 1)
  {    
    servoMotorFrequency(f);   
    servoMotorEnable(MOTOR_ENABLED);
  }
  else if (cmd == 0)
  {
    servoMotorEnable(MOTOR_DISABLED);
  }
  else
  {
    // unknown value passed to cmd
    //Serial.println("(else) stopping motor");
    servoMotorEnable(MOTOR_DISABLED);
    //Serial.print("_motor_enable Status: "); Serial.println(_motor_enable);
  }
}