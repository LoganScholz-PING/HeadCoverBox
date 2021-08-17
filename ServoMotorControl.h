#ifndef SERVOMOTORCONTROL_H
#define SERVOMOTORCONTROL_H

#include <Arduino.h>

/* === START SERVO MOTOR DEFINES === */
#define MOTOR_CCW LOW
#define MOTOR_CW HIGH
#define MOTOR_ENABLED LOW
#define MOTOR_DISABLED HIGH
#define mtrDirectionPin 8 // PH5
#define mtrPulsePin 9     // PH6
#define mtrEnablePin 10   // PB4


/***** FUNCTION PROTOTYPES *****/
/* === START SERVO MOTOR FUNCTION PROTOTYPES === */
void servoMotorSetup();
void servoMotorEnable(byte v);
void servoMotorDirection(boolean v);
void servoMotorFrequency(float f);
void servoMotorSTOP();
int servoMotorMoveDegrees(int deg);

void runMotor(int cmd, float f = 0.15);

#endif