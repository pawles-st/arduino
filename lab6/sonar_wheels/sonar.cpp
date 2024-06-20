#include <Arduino.h>
#include <Servo.h>

#include "sonar.h"

Sonar::Sonar() : servo() {}

void Sonar::init() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  servo.attach(SERVO);
}

void Sonar::next_angle() {
  angle_ctr = (angle_ctr + 1) % 13;
    switch (angle_ctr) {
      case 0:
      case 4:
      case 8: current_angle = 90; break;
      case 1:
      case 5:
      case 9: current_angle = 60; break;
      case 2:
      case 6:
      case 10: current_angle = 120; break;
      case 3: current_angle = 0; break;
      case 11: current_angle = 180; break;
      case 7: current_angle = 135; break;
      case 12: current_angle = 45; break;
    }
}

Collision Sonar::look() {
  unsigned int distance = this->tell_distance(current_angle, 50);
  byte allowed_distance = 50;
  if (abs(current_angle - 90) >= 45) {
    allowed_distance = 20;
  }

  if (distance < allowed_distance) {
    //Serial.print("WARNING AT ANGLE ");
    //Serial.println(current_angle);
    return Collision::WARNING;
  } else {
    return Collision::OK;
  }
}

void Sonar::write(byte angle) {
  servo.write(angle);
}

unsigned int Sonar::tell_distance(byte angle, int d) {
  //Serial.print("looking at angle ");
  //Serial.println(angle);
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
