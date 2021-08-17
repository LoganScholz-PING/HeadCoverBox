/*

  pin defs:
  3 - UP BUTTON INPUT (5V = pressed)
  4 - DOWN BUTTON INPUT (5V = pressed)

  8  - MOTOR DIRECTION
  9  - MOTOR PULSE
  10 - MOTOR ENABLE

*/

#include <Arduino.h>
#include "ServoMotorControl.h"

#define BTN_UP   3
#define BTN_DOWN 4

boolean motor_moving = false;

// debounce timer variable
unsigned long prev_millis = 0;
unsigned long debounce_period = 30; // milliseconds

// motor control variables
int START_MOTOR = 1;
int STOP_MOTOR  = 0;

void setup() 
{
  // 5V = true, 0V = false
  pinMode(BTN_UP,   INPUT); 
  pinMode(BTN_DOWN, INPUT);
  
  servoMotorSetup(); // sets ctrl pins, disables motor, and sets direction to CCW

  Serial.begin(9600);
}

void loop() 
{
    // debounce period has elapsed, check for buttons inputs
    // need to figure out if "up" is CW or CCW, assume CCW for now
    if(millis() - prev_millis >= 30)
    {
      if (digitalRead(BTN_UP))
      {
        servoMotorDirection(MOTOR_CCW);
        prev_millis = millis();
        runMotor(START_MOTOR);
        motor_moving = true;
        Serial.println("BUTTON UP PRESSED");
      }
      else if (digitalRead(BTN_DOWN))
      {
        servoMotorDirection(MOTOR_CW);
        prev_millis = millis();
        runMotor(START_MOTOR);
        motor_moving = true;
        Serial.println("BUTTON DOWN PRESSED");
      }
      else
      {
        if (motor_moving)
        {
          runMotor(STOP_MOTOR);
        }
      }
    }   
}