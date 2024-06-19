#include <Arduino.h>
#include <Servo.h>

#include "sonar.h"

Sonar::Sonar() : servo() {}

void Sonar::init() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servo.attach(SERVO);
}

Collision Sonar::look(byte angle) {
  Serial.println(angle);
  unsigned int distance = this->tell_distance(angle, 50);
  /*if (distance < 25) {
    return Collision::WARNING;
  }
  distance = this->tell_distance(75, 100);
  if (distance < 25) {
    return Collision::WARNING;
  }
  distance = this->tell_distance(105, 100);*/
  byte allowed_distance = 50;
  if (abs(angle - 90) >= 45) {
    allowed_distance = 20;
  }

  if (distance < allowed_distance) {
    return Collision::WARNING;
  } else {
    return Collision::OK;
  }
}

void Sonar::write(byte angle) {
  servo.write(angle);
}

unsigned int Sonar::tell_distance(byte angle, int d) {
  servo.write(angle);

  digitalWrite(TRIG, HIGH);
  delay(d);
  digitalWrite(TRIG, LOW);

  unsigned int tot = pulseIn(ECHO, HIGH);
  unsigned int distance = tot / 58;

  return distance;
}

TurnDirection Sonar::pick_direction() {
  unsigned int max_distance;

  unsigned int distance_right = this->tell_distance(0, 1000);
  Serial.print("right: ");
  Serial.println(distance_right);
  max_distance = distance_right;

  unsigned int distance_up_right = this->tell_distance(45, 1000);
  Serial.print("up right: ");
  Serial.println(distance_up_right);
  max_distance = max(max_distance, distance_up_right);
  
  unsigned int distance_up_left = this->tell_distance(135, 1000);
  Serial.print("up left: ");
  Serial.println(distance_up_left);
  max_distance = max(max_distance, distance_up_left);

  unsigned int distance_left = this->tell_distance(180, 1000);
  Serial.print("left: ");
  Serial.println(distance_left);
  max_distance = max(max_distance, distance_left);

  servo.write(90);
  Serial.print("max = ");
  Serial.println(max_distance);

  if (max_distance < 50) {
    return TurnDirection::BACK;
  } else if (distance_right == max_distance) {
    return TurnDirection::RIGHT;
  } else if (distance_up_right == max_distance) {
    return TurnDirection::UP_RIGHT;
  } else if (distance_up_left == max_distance) {
    return TurnDirection::UP_LEFT;
  } else if (distance_left == max_distance) {
    return TurnDirection::LEFT;
  }
}
