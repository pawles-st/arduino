#include <Servo.h>

#ifndef SONAR_H
#define SONAR_H

#define TRIG A0
#define ECHO A1

#define SERVO 3 // must be PWM

enum Collision {
  OK,
  WARNING,
};

class Sonar {
  public:
    Sonar();
    Collision look();
    void pick_direction();
    bool is_blocked; // is blocked by an obstacle in front
  private:
    Servo servo;
    bool waiting; // is waiting for decision confirmation
    unsigned int tell_distance(byte angle);
};

#endif
