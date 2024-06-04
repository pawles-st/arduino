#ifndef REMOTE_H
#define REMOTE_H

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

enum Command {
  COMMAND_UP,
  COMMAND_LEFT,
  COMMAND_RIGHT,
  COMMAND_DOWN,
  COMMAND_OK,
  COMMAND_NULL,
};

class Remote {
  public:
    Remote();
    init();
    Command parse_command();
  private:
    int command;
};

#endif
