#include <IRremote.h>
#include "Wheels.h"

// start code

#define BEGIN_CODE 1234

// remote control

#define IR_RECEIVE_PIN 2

#define CONTROLLER_ONE 69
#define CONTROLLER_TWO 70
#define CONTROLLER_THREE 71
#define CONTROLLER_FOUR 68
#define CONTROLLER_FIVE 64
#define CONTROLLER_SIX 67
#define CONTROLLER_SEVEN 7
#define CONTROLLER_EIGHT 21
#define CONTROLLER_NINE 9
#define CONTROLLER_ZERO 25

#define CONTROLLER_STAR 22
#define CONTROLLER_HASH 13

#define CONTROLLER_UP 24
#define CONTROLLER_LEFT 8
#define CONTROLLER_RIGHT 90
#define CONTROLLER_DOWN 82
#define CONTROLLER_OK 28

// start code
volatile int code;

// movement variables
volatile int command;
unsigned long prev_time = 0;
unsigned long command_delay = 100;
Wheels w;
unsigned int MAX_SPEED = 1000;

void setup() {
  Serial.begin(9600);

  // insert code before starting the loop

  while (true) {
    code = Serial.parseInt();
    if (code == BEGIN_CODE) {
      Serial.println("Code correct; starting now.");
      break;
    } else {
      Serial.println("CODE INCORRECT.");
    }
  }

  // begin receiving signals

  IrReceiver.begin(IR_RECEIVE_PIN);

  // attaching wheel pins

  w.attach(7,8,5,12,11,10);
  w.setSpeed(100);
}

void loop() {
  unsigned long curr_time = millis();
  if (curr_time - prev_time > command_delay) {
    prev_time = curr_time;
    if (IrReceiver.decode()) {
      IrReceiver.resume();
      command = IrReceiver.decodedIRData.command;
      switch (command) {
        case CONTROLLER_UP: w.forward(); break;
        case CONTROLLER_LEFT: break;
        case CONTROLLER_RIGHT: break;
        case CONTROLLER_DOWN: w.back(); break;
        case CONTROLLER_OK: w.stop(); break;
        case CONTROLLER_ONE: w.setSpeed(100); break;
        case CONTROLLER_TWO: w.setSpeed(150); break;
        case CONTROLLER_THREE: w.setSpeed(200); break;
        case CONTROLLER_FOUR: w.setSpeed(MAX_SPEED); break;
      }
    } else {
      w.stop();
    }
  }
}
