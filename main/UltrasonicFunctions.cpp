#include "UltraSonicFunctions.h"

// const int leftPing = A0;
// const int leftEcho = A1;
const int centrePing = 7;
const int centreEcho = 6;
// const int rightPing = A2;
// const int rightEcho = A3;

const int rightPing = A0;
const int rightEcho = A1;
const int leftPing = A2;
const int leftEcho = A3;
bool wallFront() {
  // Serial.print('Centre :');
  int distance = ultrasonicDistance(centrePing, centreEcho);
  // Serial.println(distance);
  return ultrasonicDistance(centrePing, centreEcho) < WALL_THRESHOLD_FRONT;
}

bool wallRight() {
  int distance = ultrasonicDistance(rightPing, rightEcho);
  // Serial.print('Right :');
  // Serial.println(distance);
  return distance < WALL_THRESHOLD_SIDE;
}

bool wallLeft() {
  // Serial.print('Left :');
  int distance = ultrasonicDistance(leftPing, leftEcho);
  // Serial.println(distance); 
  // Serial.println(ultrasonicDistance(leftPing, leftEcho));
    return ultrasonicDistance(leftPing, leftEcho) < WALL_THRESHOLD_SIDE;
}

int ultrasonicDistance(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}


void setup_ultrasonic(){
    pinMode(leftPing, OUTPUT);
    pinMode(leftEcho, INPUT);
    pinMode(rightPing, OUTPUT);
    pinMode(rightEcho, INPUT);
    pinMode(centrePing, OUTPUT);
    pinMode(centreEcho, INPUT);
}
