#include "UltrasonicFunctions.h"

const int leftPing = A0;
const int leftEcho = A1;
const int rightPing = 7;
const int rightEcho = 6;
const int centrePing = A2;
const int centreEcho = A3;

int ultrasonicDistance(int triggerPin, int echoPin) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

bool wallFront() {
    return ultrasonicDistance(centrePing, centreEcho) < WALL_THRESHOLD;
}

bool wallRight() {
    return ultrasonicDistance(rightPing, rightEcho) < WALL_THRESHOLD;
}

bool wallLeft() {
    return ultrasonicDistance(leftPing, leftEcho) < WALL_THRESHOLD;
}
void setup_ultrasonic(){
    pinMode(leftPing, OUTPUT);
    pinMode(leftEcho, INPUT);
    pinMode(rightPing, OUTPUT);
    pinMode(rightEcho, INPUT);
    pinMode(centrePing, OUTPUT);
    pinMode(centreEcho, INPUT);
}
