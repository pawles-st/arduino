#include "Wheels.h"
#include "lcd.h"
#include "passcode.h"
#include "remote.h"

///// MOVEMENT DECLARATION /////

Wheels w; // car movement controller object
int distance_to_travel; // expected distance to travel for a goForward/goBackward command
float distance_travelled; // distance travelled during a time frame between loops
#define CM_PER_MS 0.005 // centimeters travelled by the car in a millisecond

///// LCD DECLARATION /////

LCD lcd; // lcd controller object
unsigned long prev_print_time; // (timer) previous LCD print time
#define LCD_DELAY 1000 // delay between consecutive prints on the LCD display

///// Remote variables /////

Command command; // current command
Remote remote_control;
unsigned long prev_command_time; // previous command read time
#define COMMAND_DELAY 100 // delay between consecutive command reads

///// universal timing variables /////

unsigned long prev_time; // time measured in the previous loop
unsigned long curr_time; // time measured in the current loop

///// initialisation /////

void setup() {

  // setup serial
  
  Serial.begin(9600);

  // input passcode

  //input_passcode();
  
  // attaching wheel pins

  w.attach(7,8,5,12,11,10);

  // setup LCD

  lcd.init();

  // setup remote

  remote_control.init();
}

///// main program loop /////

void loop() {

  // get current time

  curr_time = millis();

  // monitor distance travelled

  float distance_travelled = (curr_time - prev_time) * CM_PER_MS;
  w.monitorDistance(distance_travelled);

  // print info on LCD

  if (curr_time - prev_print_time > LCD_DELAY) {
    prev_print_time = curr_time;
    lcd.clear();
    lcd.update_animation(w.right_state, w.left_state);
    lcd.print_movement_info(w.distance_left, w.right_state, w.left_state);
  }

  // parse commands

  if (curr_time - prev_command_time > COMMAND_DELAY) {
    prev_command_time = curr_time;
    Command cmd = remote_control.parse_command();
    Serial.println(cmd);
    switch (cmd) {
      case Command::COMMAND_UP: w.forward(); break;
      case Command::COMMAND_LEFT: w.turnLeft(); break;
      case Command::COMMAND_RIGHT: w.turnRight(); break;
      case Command::COMMAND_DOWN: w.back(); break;
      case Command::COMMAND_OK: break;
      default: w.stop();
    }
  }

  prev_time = curr_time;
}