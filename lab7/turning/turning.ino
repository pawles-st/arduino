#include "Wheels.h"

Wheels w;

unsigned long curr_time;

unsigned long prev_command_time = 0;
unsigned long command_delay = 100;

bool is_turning_right = false;
unsigned long turn_right_start_time = 0;
unsigned long turn_right_duration = 1000;

bool is_turning_left = false;
unsigned long turn_left_start_time = 0;
unsigned long turn_left_duration = 1000;

void setup() {
  Serial.begin(9600);

  w.attach(7,8,5,12,11,10);
  w.setSpeed(100);
}

void loop() {
  unsigned long curr_time = millis();

  if (is_turning_right && curr_time - turn_right_start_time > turn_right_duration) {
    is_turning_right = false;
    Serial.println("stopping turning right");
    w.stop();
  }

  if (is_turning_left && curr_time - turn_left_start_time > turn_left_duration) {
    is_turning_left = false;
    Serial.println("stopping turning left");
    w.stop();
  }

  if (curr_time - prev_command_time > command_delay) {
    char command = Serial.read();
    switch (command) {
      case 'r': turnRight(); is_turning_right = true; turn_right_start_time = millis(); break;
      case 'l': turnLeft(); is_turning_left = true; turn_left_start_time = millis(); break;
      case 's': w.stop(); break;
    }
  }
}

void turnRight() {
  Serial.println("turning right...");
  w.setSpeedRight(100);
  w.backRight();
  w.setSpeedLeft(100);
  w.forwardLeft();
}

void turnLeft() {
  Serial.println("turning left...");
  w.setSpeedRight(100);
  w.forwardRight();
  w.setSpeedLeft(100);
  w.backLeft();
}