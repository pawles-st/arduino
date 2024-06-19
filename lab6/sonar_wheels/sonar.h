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
    Collision look(byte angle);
    TurnDirection pick_direction();
    void write(byte angle);
    bool is_blocked; // is blocked by an obstacle in front
  private:
    Servo servo;
    int find_min(int a, int b, int c, int d);
    bool waiting; // is waiting for decision confirmation
    unsigned int tell_distance(byte angle, int d);
};

#endif
