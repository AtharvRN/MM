#include <Wire.h>
#include <mpu6050.h>
#include "UltrasonicFunctions.h"
#include "EncoderFunctions.h"
#include "MotorPIDFunctions.h"


// all distances in mm
#define CELL_SIZE 150
#define WHEEL_CIRCUMFERENCE 66
#define NUM_ENCODER_TICKS 20
#define ANGLE_THRESHOLD 1

void turnRight() {
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir - 90;
  int steer;
  pid_reset();
  while(current_dir - target_dir <= ANGLE_THRESHOLD || current_dir -target_dir >= -ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    motor_move(0,steer);
    delay(5);
  }
  motor_off();
}

void turnLeft() {
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir + 90;
  int steer;
  pid_reset();
  while(current_dir - target_dir <= ANGLE_THRESHOLD || current_dir -target_dir >= -ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    motor_move(0,steer);
    delay(5);
  }
  motor_off();
}

void moveForward(int cells = 1) {
    float target = cells * CELL_SIZE;  
    unsigned long init_ticksA = get_tickA();  
    unsigned long init_ticksB = get_tickB();
    float distance = 0;
    pid_reset();
    float prevYaw = mpu6050_yaw();
    float currYaw;
    while (distance < target) {

      currYaw = mpu6050_yaw(); 
      int steer = (int)pid(currYaw - prevYaw);
      prevYaw = currYaw;
      motor_move(200,steer);  

      unsigned long ticksA =  get_tickA() - init_ticksA;
      unsigned long ticksB =  get_tickB() - init_ticksB;
      float distanceA = (ticksA/NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
      float distanceB = (ticksB/NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
      distance = (distanceA + distanceB)/2 ;
    }
    motor_off();  
}

void setup(){
  motor_begin();
  setupEncoders();
  setup_ultrasonic();
  pid_reset();

}

void loop(){


}