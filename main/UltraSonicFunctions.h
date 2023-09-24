#ifndef UltrasonicFunctions_h
#define UltrasonicFunctions_h

#include "Arduino.h"

#define WALL_THRESHOLD 20  // in cm

int ultrasonicDistance(int triggerPin, int echoPin);
bool wallFront();
bool wallRight();
bool wallLeft();
void setup_ultrasonic();
#endif
