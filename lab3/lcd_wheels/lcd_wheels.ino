#include "Wheels.h"
#include "lcd.h"

///// MOVEMENT DECLARATION /////

// objects & variables

Wheels w; // car movement controller object
int distance_to_travel; // expected distance to travel for a goForward/goBackward command
float distance_travelled; // distance travelled during a time frame between loops

// constants

#define CM_PER_MS 0.005 // centimeters travelled by the car in a millisecond

///// LCD DECLARATION /////

// objects & variables

LCD lcd; // lcd controller object
unsigned long prev_print_time; // (timer) previous LCD print time

// constants

#define LCD_DELAY 1000 // delay between consecutive prints on the LCD display

///// command variables

char cmd; // current command
unsigned long prev_command_time; // previous command read time
#define COMMAND_DELAY 100 // delay between consecutive command reads

///// universal timing variables

unsigned long prev_time; // time measured in the previous loop
unsigned long curr_time; // time measured in the current loop

///// initialisation

void setup() {

  // setup serial
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");
  
  // attaching wheel pins

  w.attach(7,8,5,12,11,10);

  // setup LCD

  lcd.init();

}

///// main program loop

void loop() {

  // get current time

  curr_time = millis();

  // monitor distance travelled

  monitor_distance();

  // print info on LCD

  if (curr_time - prev_print_time > LCD_DELAY) {
    prev_print_time = curr_time;
    Serial.print("resetting...");
    lcd.clear();
    lcd.update_animation(w.right_state, w.left_state);
    lcd.print_movement_info(w.distance_left, w.right_state, w.left_state);
  }

  // parse commands

  if (curr_time - prev_command_time > COMMAND_DELAY) {
    prev_command_time = curr_time;
    while (Serial.available()) {
      cmd = Serial.read();
      Serial.println(cmd);
      move();
    }
  }

  prev_time = curr_time;
}

void monitor_distance() {
  if (w.is_travelling == true) {

    // update current distance

    distance_travelled = (curr_time - prev_time) * CM_PER_MS;
    if (w.distance_left > distance_travelled) {
      w.distance_left -= distance_travelled;
    } else {

      // stop if travelled expected distance

      w.distance_left = 0;
      w.stop();
      w.is_travelling = false;
    }
  }
} 

void move() {
  switch (cmd) {
    case 'w': w.forward(); break;
    case 'x': w.back(); break;
    case 'a': w.forwardLeft(); break;
    case 'd': w.forwardRight(); break;
    case 'z': w.backLeft(); break;
    case 'c': w.backRight(); break;
    case 's': w.stop(); break;
    case '1': w.setSpeedLeft(75); break;
    case '2': w.setSpeedLeft(200); break;
    case '9': w.setSpeedRight(75); break;
    case '0': w.setSpeedRight(200); break;
    case '5': w.setSpeed(100); break;
    case 'f': distance_to_travel = Serial.parseInt(SKIP_ALL); w.goForward(distance_to_travel); w.is_travelling = true; break;
    case 'b': distance_to_travel = Serial.parseInt(SKIP_ALL); w.goBack(distance_to_travel); w.is_travelling = true; break;
  }
}