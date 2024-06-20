#include <IRremote.h>

#include "remote.h"

Remote::Remote() {}

Remote::init() {
  IrReceiver.begin(IR_RECEIVE_PIN);
}

Command Remote::parse_command() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    switch (command) {
      case CONTROLLER_UP: return Command::COMMAND_UP; break;
      case CONTROLLER_LEFT: return Command::COMMAND_LEFT; break;
      case CONTROLLER_RIGHT: return Command::COMMAND_RIGHT; break;
      case CONTROLLER_DOWN: return Command::COMMAND_DOWN; break;
      case CONTROLLER_OK: return Command::COMMAND_OK; break;
    }
    /*
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
    */
  } else if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'w': return Command::COMMAND_UP; break;
      case 'a': return Command::COMMAND_LEFT; break;
      case 'd': return Command::COMMAND_RIGHT; break;
      case 's': return Command::COMMAND_DOWN; break;
      case 'z': return Command::COMMAND_OK; break;
      case 'f': return Command::COMMAND_FORWARD; break;
      case 'b': return Command::COMMAND_BACKWARD; break;
    }
  } else {
    return Command::COMMAND_NULL;
  }
}