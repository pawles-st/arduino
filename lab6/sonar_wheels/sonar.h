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

enum TurnDirection {
  LEFT,
  UP_LEFT,
  UP_RIGHT,
  RIGHT,
  BACK,
};

class Sonar {
  public:
    Sonar();
    void init();
    void next_angle();
    Collision look();
    TurnDirection pick_direction();
    void write(byte angle);
    bool is_blocked; // is blocked by an obstacle in front
    byte current_angle = 90;
  private:
    Servo servo;
    byte angle_ctr = 0;
    unsigned int tell_distance(byte angle, int d);
};

#endif
