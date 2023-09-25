#include <Wire.h>
#include "mpu6050.h"
#include "UltraSonicFunctions.h"
#include "EncoderFunctions.h"
#include "MotorPIDFunctions.h"
#include "robot_moves.h"
// #include "floodfill.h"


void setup(){
  delay(500);
  // Serial.begin(115200);
  motor_begin();
  mpu6050_begin();
  // Serial.println("Basi");
  setupEncoders();
  setup_ultrasonic();
  pid_reset();
  gotoTarget(0, 0, DIR_UP);

  delay(500);
  moveForward(750);
  delay(500);
  turnRight();
  delay(500);
  moveForward(650);
  delay(500);
  turnRight();
  moveForward(600);
  delay(500);
  turnLeft();
  delay(500);
  moveForward(650);
  delay(500);
  turnLeft();
  delay(500);
  moveForward(700);
  delay(500);
  moveForward(700);
  delay(500);
  turnRight();
  delay(500);
  moveForward(650);
 

}

const int centrePing = 7;
const int centreEcho = 6;
const int rightPing = A2;
const int rightEcho = A3;


const int leftPing = A0;
const int leftEcho = A1;

void loop(){
  // Serial.println(wallRight());
delay(1000);
int Rd = ultrasonicDistance(rightPing, rightEcho);
int Ld = ultrasonicDistance(leftPing, leftEcho);
int Cd = ultrasonicDistance(centrePing, centreEcho);
// Serial.print("right : ");
// Serial.println(Rd);
// Serial.print("left : ");
// Serial.println(Ld);
// Serial.print("centre : ");
// Serial.println(Cd);
  if(Rd > 10){
    Serial.println("R");
    turnRight();
  }
  else if(Ld > 10){
    Serial.println("L");
    turnLeft();
  }
  else if(Cd > 10){
    Serial.println("F");
    moveForward();
  }

  motor_off();
//   delay(100);
  // Serial.println(distance);


}
