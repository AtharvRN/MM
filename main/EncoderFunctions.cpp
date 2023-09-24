#include "EncoderFunctions.h"

const int encoderPinA = 3; 
const int encoderPinB = 2;  

volatile unsigned long encoderTicksA = 0;
volatile unsigned long encoderTicksB = 0;

void encoderISR_A() {
    encoderTicksA++;
}

void encoderISR_B() {
    encoderTicksB++;
}

void setupEncoders() {
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderISR_A, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), encoderISR_B, RISING);
}
unsigned long get_tickA(){
  return encoderTicksA;
}
unsigned long get_tickB(){
  return encoderTicksB;
}
