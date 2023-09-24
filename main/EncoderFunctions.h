#ifndef EncoderFunctions_h
#define EncoderFunctions_h

#include "Arduino.h"

void encoderISR_A();
void encoderISR_B();
void setupEncoders();
unsigned long get_tickA();
unsigned long get_tickB();
#endif
