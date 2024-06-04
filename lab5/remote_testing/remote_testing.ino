#include <IRremote.h>

#define BEGIN_CODE 1234

#define IR_RECEIVE_PIN 2
#define CONTROLLER_ONE 69
#define CONTROLLER_TWO 70
#define CONTROLLER_THREE 71
#define CONTROLLER_FOUR 68
#define CONTROLLER_FIVE 64
#define CONTROLLER_SIX 67
#define CONTROLLER_ONE 7
#define CONTROLLER_ONE 21
#define CONTROLLER_ONE 9
#define CONTROLLER_ZERO 25

#define CONTROLLER_STAR 22
#define CONTROLLER_HASH 13

#define CONTROLLER_UP 24
#define CONTROLLER_LEFT 8
#define CONTROLLER_RIGHT 90
#define CONTROLLER_DOWN 82
#define CONTROLLER_OK 28

int code;

void setup() {
  Serial.begin(9600);

  // insert code before starting the loop

  while (true) {
    code = Serial.parseInt();
    if (code == BEGIN_CODE) {
      break;
    }
  }

  // begin receiving signals

  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
  }
}
