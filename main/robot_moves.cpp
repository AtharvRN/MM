#include "robot_moves.h"

#include <Wire.h>
#include "mpu6050.h"
#include "EncoderFunctions.h"
#include "MotorPIDFunctions.h"

// all distances in mm
#define CELL_SIZE 300
#define WHEEL_CIRCUMFERENCE 208
#define NUM_ENCODER_TICKS 20
#define ANGLE_THRESHOLD 3

void turnRight() {
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir - 90;
  
  int steer;
  unsigned long start = millis();
  pid_reset();
  while(current_dir - target_dir <= -ANGLE_THRESHOLD || current_dir -target_dir >= ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    current_dir = mpu6050_yaw();
  //   Serial.print("yaw:");
  // Serial.println(current_dir);
    // Serial.print("steer :");
    // Serial.println(steer);
    // int thres = 5;
    // if (steer < thres && steer > -thres) {
    //   steer = steer > 0 ? thres : -thres;
    // }
    if(millis() - start > 3000){
      break;
    }
    motor_move(0,steer);

  }
  motor_off();
}

void turnLeft() {
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir + 90;
  int steer;
  unsigned long start = millis();
  pid_reset();
  while(current_dir - target_dir <= -ANGLE_THRESHOLD || current_dir -target_dir >= ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    current_dir = mpu6050_yaw();
    motor_move(0,steer);
    if(millis() - start > 3000){
      break;
    }
    // delay(5);
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
      motor_A_set(200);
      motor_B_set(200);
      // motor_move(200,steer);  
      // Serial.print("steer : ");
      // Serial.println(steer);
      // Serial.print("ticksA : ");
      // Serial.println(get_tickA());
      // Serial.print("ticksB : ");
      // Serial.println(get_tickB());
      unsigned long ticksA =  get_tickA() - init_ticksA;
      unsigned long ticksB =  get_tickB() - init_ticksB;
      float distanceA = (ticksA/NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
      float distanceB = (ticksB/NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
      Serial.print("distanceA : ");
      Serial.println(distanceA);

      Serial.print("distanceB : ");
      Serial.println(distanceB);

      distance = (distanceA + distanceB)/2 ;
    }
    motor_off();  
}

// void setup(){
//   motor_begin();
//   setupEncoders();
//   setup_ultrasonic();
//   pid_reset();

// }

// void loop(){


// }
