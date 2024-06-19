#include <Arduino.h>

#include "Wheels.h"

#define SPEED_LEFT 158
#define SPEED_RIGHT 140

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() : left_state(EngineState::STOP), right_state(EngineState::STOP) {}

void Wheels::attachRight(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::setSpeedRight(uint8_t s)
{
    analogWrite(this->pinsRight[2], s);
}

void Wheels::setSpeedLeft(uint8_t s)
{
    analogWrite(this->pinsLeft[2], s);
}

void Wheels::setSpeed(uint8_t s)
{
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() 
{
    this->setSpeedLeft(SPEED_LEFT);
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
    this->distance_left = 0;
    this->left_state = EngineState::FORWARD;
}

void Wheels::forwardRight() 
{
    this->setSpeedRight(SPEED_RIGHT);
    SET_MOVEMENT(pinsRight, HIGH, LOW);
    this->distance_left = 0;
    this->right_state = EngineState::FORWARD;
}

void Wheels::backLeft()
{
    this->setSpeedLeft(SPEED_LEFT);
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
    this->distance_left = 0;
    this->left_state = EngineState::BACKWARD;
}

void Wheels::backRight()
{
    this->setSpeedRight(SPEED_RIGHT);
    SET_MOVEMENT(pinsRight, LOW, HIGH);
    this->distance_left = 0;
    this->right_state = EngineState::BACKWARD;
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, LOW);
    this->distance_left = 0;
    this->left_state = EngineState::STOP;
}

void Wheels::stopRight()
{
    SET_MOVEMENT(pinsRight, LOW, LOW);
    this->distance_left = 0;
    this->right_state = EngineState::STOP;
}

void Wheels::stop()
{
    this->stopLeft();
    this->stopRight();
}

void Wheels::goForward(uint8_t cm) {
    this->forward();
    this->setSpeed(100);
    this->distance_left = cm;
}

void Wheels::goBack(uint8_t cm) {
    this->back();
    this->setSpeed(100);
    this->distance_left = cm;
}

void Wheels::turnLeft() {
  Serial.println("turn left");
  this->backLeft();
  this->forwardRight();
  this->setSpeedLeft(160);
  this->setSpeedRight(220);
}

void Wheels::turnRight() {
  Serial.println("turn right");
  this->forwardLeft();
  this->backRight();
  this->setSpeedLeft(160);
  this->setSpeedRight(220);
}

void Wheels::monitorDistance(float distance_travelled) {
  if (this->is_travelling == true) {

    // update current distance

    if (this->distance_left > distance_travelled) {
      this->distance_left -= distance_travelled;
    } else {

      // stop if travelled expected distance

      this->distance_left = 0;
      this->stop();
      this->is_travelling = false;
    }
  }
}


