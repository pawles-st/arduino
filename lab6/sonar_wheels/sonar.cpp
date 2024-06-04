#include <Arduino.h>
#include <Servo.h>

#include "sonar.h"

Sonar::Sonar() : servo() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servo.attach(SERVO);

  servo.write(90);
}

Collision Sonar::look() {
  unsigned int distance = this->tell_distance(90);
  if (distance < 100) {
    return Collision::WARNING;
  } else {
    return Collision::OK;
  }
}

unsigned int Sonar::tell_distance(byte angle) {
  servo.write(angle);

  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);

  unsigned int tot = pulseIn(ECHO, HIGH);
  unsigned int distance = tot / 58;

  return distance;
}

void Sonar::pick_direction() {

}
