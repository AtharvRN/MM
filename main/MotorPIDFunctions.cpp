#include "MotorPIDFunctions.h"

MPU6050 mpu6050;

#define MOTOR_A_IN1  11
#define MOTOR_A_IN2  12
#define MOTOR_A_ENA  9

#define MOTOR_B_IN1  4
#define MOTOR_B_IN2  5
#define MOTOR_B_ENA  10

#define MAX_SPEED 255
void motor_begin() {
  
  
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_A_ENA, OUTPUT);

  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  pinMode(MOTOR_B_ENA, OUTPUT);  

  analogWrite(MOTOR_A_ENA, 0);
  analogWrite(MOTOR_B_ENA, 0);

  Serial.println("Motors : Setup");
}

void motor_A_set( int speed ) {
  // Serial.print("Speed : ");
  // Serial.println(speed);
  if( speed==0 ) {
    digitalWrite( MOTOR_A_IN1, HIGH );
    digitalWrite( MOTOR_A_IN2, HIGH );
    analogWrite(MOTOR_A_ENA, 0);    
  } else if( speed>0 ) {
    digitalWrite( MOTOR_A_IN1, HIGH );
    digitalWrite( MOTOR_A_IN2, LOW );
    analogWrite ( MOTOR_A_ENA, speed);        
  } else {
    digitalWrite( MOTOR_A_IN1, LOW );
    digitalWrite( MOTOR_A_IN2, HIGH );
    analogWrite ( MOTOR_A_ENA, -speed);            
  }
}

void motor_B_set( int speed ) {
  if( speed==0 ) {
    digitalWrite( MOTOR_B_IN1, HIGH );
    digitalWrite( MOTOR_B_IN2, HIGH );
    analogWrite(MOTOR_B_ENA, 0);    
  } else if( speed>0 ) {
    digitalWrite( MOTOR_B_IN1, HIGH );
    digitalWrite( MOTOR_B_IN2, LOW );
    analogWrite ( MOTOR_B_ENA, speed);        
  } else {
    digitalWrite( MOTOR_B_IN1, LOW );
    digitalWrite( MOTOR_B_IN2, HIGH );
    analogWrite ( MOTOR_B_ENA, -speed);            
  }
}

void motor_off() {
  digitalWrite( MOTOR_A_ENA, 0 );
  digitalWrite( MOTOR_B_ENA, 0 );
}

void motor_move(int speed,int delta) {
  // Serial.print("speed : ");
  // Serial.println(speed);
  // Serial.print("delta :" );
  // Serial.print(delta);
  int setL = speed + delta;
  int setR = speed - delta;
  if( setL> MAX_SPEED) 
      setL = MAX_SPEED;
  if( setR> MAX_SPEED) 
      setR = MAX_SPEED;
  if( setL < -MAX_SPEED) 
      setL = -MAX_SPEED;
  if( setR < -MAX_SPEED) 
      setR = -MAX_SPEED;

  // Serial.print("delta : ");
  // Serial.println(delta);
  // Serial.print("Left:");
  // Serial.println(setL);

  // Serial.print("Right:");
  // Serial.println(setR);

  motor_A_set(setL);
  motor_B_set(setR );
}

void motor_basic(){
  motor_A_set(250);
  motor_B_set(250);
}

#define PID_K_p 2
#define PID_K_i  0
#define PID_K_d  0

float i_input;
float d_last;

void pid_reset() {
  i_input= 0;
  d_last= 0;  
  Serial.println("PID : reset");
}

int pid(float error) {
  float p_input;
  float d_input;
    
  p_input= error;
  i_input= constrain(i_input+error,-50,+50);
  d_input= error-d_last; d_last=error;

  return p_input*PID_K_p + i_input*PID_K_i + d_input*PID_K_d;
}
void mpu6050_begin()  {
  Wire.begin();
  Serial.print("MPU6050: Starting calibration; leave device flat and still ... ");
  int error= mpu6050.begin(); 
  Serial.println(mpu6050.error_str(error));
}

float mpu6050_yaw() {
  MPU6050_t data= mpu6050.get();
  while( data.dir.error!=0 ) { 
    // I suffer from a lot of I2C problems
    Serial.println(mpu6050.error_str(data.dir.error));
    // Reset I2C
    TWCR= 0; Wire.begin();
    // Reread
    data= mpu6050.get();
  }
  return data.dir.yaw;
}

