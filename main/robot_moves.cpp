#include "robot_moves.h"

#include <Wire.h>
#include "mpu6050.h"
#include "EncoderFunctions.h"
#include "MotorPIDFunctions.h"

// all distances in mm
#define CELL_SIZE 600;
#define WHEEL_CIRCUMFERENCE 208
#define NUM_ENCODER_TICKS 20
#define ANGLE_THRESHOLD 3

// void turnLeft() {
//   delay(500);
//   motor_A_set(100);
//   motor_B_set(-100);
//   delay(550);
//   motor_off();
// }

// void turnRight() {
//   delay(500);
//   motor_A_set(-100);
//   motor_B_set(100);
//   delay(550);
//   motor_off();
// }

// void moveForward(int cells = 1) {
//   Serial.println("forward");
//     float target = cells * CELL_SIZE * 4;  
//     unsigned long init_ticksA = get_tickA();  
//     unsigned long init_ticksB = get_tickB();
//     float distance = 0;
//     while (distance < target) {

//       motor_A_set(100);
//       motor_B_set(108);
//       unsigned long ticksA =  get_tickA() - init_ticksA;
//       unsigned long ticksB =  get_tickB() - init_ticksB;
//       float distanceA = (ticksA/(float)NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
//       float distanceB = (ticksB/(float)NUM_ENCODER_TICKS) * WHEEL_CIRCUMFERENCE;
//       // Serial.print("distanceA : ");
//       // Serial.println(distanceA);

//       // Serial.print("distanceB : ");
//       // Serial.println(distanceB);

//       distance = (distanceA + distanceB)/2 ;
//     }
//     motor_off();  
// }


void turnRight() {
  // Serial.println("right");
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir - 90;
  
  int steer;
  unsigned long start = millis();
  pid_reset();
  while(current_dir - target_dir <= -ANGLE_THRESHOLD || current_dir -target_dir >= ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    current_dir = mpu6050_yaw();
    if(millis() - start > 3000){
      break;
    }
    motor_move(0,steer);

  }
  motor_off();
}

void turnLeft() {
  // Serial.println("left");
  float current_dir = mpu6050_yaw();
  float target_dir = current_dir + 90;
  int steer;
  unsigned long start = millis();
  pid_reset();
  while(current_dir - target_dir <= -ANGLE_THRESHOLD || current_dir -target_dir >= ANGLE_THRESHOLD){
    steer = (int)pid( target_dir - current_dir );
    current_dir = mpu6050_yaw();
    if(millis() - start > 3000){
      break;
    }
    motor_move(0,steer);
    // delay(5);
  }
  motor_off();
}


void moveForward(int target = 600) {
  // Serial.println("forward");
    // float target = cells * CELL_SIZE;  
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
      // motor_A_set(200);
      // motor_B_set(200);
      motor_move(200,steer);  
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
      // Serial.print("distanceA : ");  
      // Serial.println(distanceA);

      // Serial.print("distanceB : ");
      // Serial.println(distanceB);

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
