#include "Wheels.h"
#include "lcd.h"
#include "passcode.h"
#include "remote.h"
#include "sonar.h"

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

Remote remote_control; // remote controller object
unsigned long prev_command_time; // previous command read time
#define COMMAND_DELAY 100 // delay between consecutive command reads

///// Sonar variables /////

Sonar sonar; // sonar controller object
unsigned long prev_sonar_time; // previous sonar monitor time
TurnDirection turn_direction;
byte angle_ctr = 0;
byte current_angle = 90;
#define SONAR_DELAY 500 // delay between consecutive sonar reads

///// universal timing variables /////

unsigned long prev_time; // time measured in the previous loop
unsigned long curr_time; // time measured in the current loop

///// behavioural variables /////

bool autonomous = false;

///// initialisation /////

void setup() {

  // setup serial
  
  Serial.begin(9600);

  // input passcode

  //input_passcode();
  
  // attaching wheel pins

  w.attach(4,7,5,9,8,6);

  // setup LCD

  lcd.init();

  // setup remote

  remote_control.init();

  // setup sonar

  sonar.init();
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
    Command command = remote_control.parse_command();
    if (command == Command::COMMAND_OK) {
      autonomous = !autonomous;
    }
    if (sonar.is_blocked) {
      Serial.println(turn_direction);
      if (turn_direction == TurnDirection::RIGHT) {
        w.turnRight();
        delay(600);
        w.stop();
      } else if (turn_direction == TurnDirection::UP_RIGHT) {
        w.turnRight();
        delay(300);
        w.stop();
      } else if (turn_direction == TurnDirection::UP_LEFT) {
        w.turnLeft();
        delay(300);
        w.stop();
      } else if (turn_direction == TurnDirection::LEFT) {
        w.turnLeft();
        delay(600);
        w.stop();
      } else if (turn_direction == TurnDirection::BACK) {
        w.back();
        delay(1000);
        w.turnLeft();
        delay(1000);
        w.stop();
      }
      sonar.is_blocked = false;
    } else {
      prev_command_time = curr_time;
      switch (command) {
        case Command::COMMAND_UP: w.forward(); break;
        case Command::COMMAND_LEFT: w.turnLeft(); break;
        case Command::COMMAND_RIGHT: w.turnRight(); break;
        case Command::COMMAND_DOWN: w.back(); break;
        default: if (autonomous) {w.forward();} else {w.stop();}
      }
    }
  }

  // monitor for obstacles

  if (autonomous && curr_time - prev_sonar_time > SONAR_DELAY) {
    prev_sonar_time = curr_time;
    switch (sonar.look(current_angle)) {
      case Collision::OK: break;
      case Collision::WARNING: w.stop(); sonar.is_blocked = true; turn_direction = sonar.pick_direction(); break;
    }

    angle_ctr = (angle_ctr + 1) % 13;
    switch (angle_ctr) {
      case 0:
      case 4:
      case 8: current_angle = 90; break;
      case 1:
      case 5:
      case 9: current_angle = 60; break;
      case 2:
      case 6:
      case 10: current_angle = 120; break;
      case 3: current_angle = 0; break;
      case 11: current_angle = 180; break;
      case 7: current_angle = 135; break;
      case 12: current_angle = 45; break;
    }
  }

  prev_time = curr_time;
}