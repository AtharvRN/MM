#ifndef MotorPIDFunctions_h
#define MotorPIDFunctions_h

#include "Arduino.h"
#include <Wire.h>
#include "mpu6050.h"

void mpu6050_begin();
float mpu6050_yaw();
void motor_begin();
void motor_A_set(int);
void motor_B_set(int);
void motor_off();
void motor_move(int,int);
void pid_reset();
int pid(float);
void motor_basic();

#endif
