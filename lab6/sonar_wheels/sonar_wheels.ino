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
int distance = 0;

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
  //Serial.println(autonomous);

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

    Command command = remote_control.parse_command();

    if (command == Command::COMMAND_OK) {
      if (autonomous) {
        sonar.current_angle = 90;
      }
      autonomous = !autonomous;
    }
  
    if (!autonomous) {
        switch (command) {
        case Command::COMMAND_UP: if (!sonar.is_blocked) {w.forward();} break;
        case Command::COMMAND_LEFT: w.turnLeft(); break;
        case Command::COMMAND_RIGHT: w.turnRight(); break;
        case Command::COMMAND_DOWN: w.back(); break;
        case Command::COMMAND_FORWARD: distance = Serial.parseInt(); w.goForward(distance); break;
        case Command::COMMAND_BACKWARD: distance = Serial.parseInt(); w.goBack(distance); break;
        default: w.stop();
      }
    } else {
      w.forward();
    }
  }

  // monitor for obstacles

  if (curr_time - prev_sonar_time > SONAR_DELAY) {
    prev_sonar_time = curr_time;
    
    // look for obstacle at current angle

    //Serial.println("looking...");
    switch (sonar.look()) {
      case Collision::OK: sonar.is_blocked = false; break;
      case Collision::WARNING: w.stop(); sonar.is_blocked = true; break;
    }

    // update next looking angle (only if autonomous, otherwise keep looking in front)

    if (autonomous) {
      //Serial.println("next angle...");
      sonar.next_angle();
    }
  }

  // handle obstacle avoidance

  if (autonomous && sonar.is_blocked) {

    // pick an optimal direction and turn

    turn_direction = sonar.pick_direction();
    switch (turn_direction) {
      case TurnDirection::RIGHT: w.turnRight(); delay(600); w.stop(); break;
      case TurnDirection::UP_RIGHT: w.turnRight(); delay(300); w.stop(); break;
      case TurnDirection::UP_LEFT: w.turnLeft(); delay(300); w.stop(); break;
      case TurnDirection::LEFT: w.turnLeft(); delay(600); w.stop(); break;
      case TurnDirection::BACK: w.back(); delay(1000); w.turnLeft(); delay(1000); w.stop(); break;
    }

    // remove the movement blockade

    sonar.is_blocked = false;
  }

  prev_time = curr_time;
}