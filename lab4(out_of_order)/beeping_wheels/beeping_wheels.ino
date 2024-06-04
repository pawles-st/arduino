// obwód koła: 21 cm

#include "Wheels.h"
#include "TimerOne.h"

//byte LCDAddress = 0x27;

//LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

// Movement variables

Wheels w;
volatile char cmd;
volatile char distance;

// Movement beeping

#define BEEPER 13
bool beeping = false;
uint8_t beep_state;
const long int beep_delay = 500000;

void setup() {
  
  // attaching wheel pins

  w.attach(7,8,5,12,11,10);

  // setup serial
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

  // add beeping interrupt

  pinMode(BEEPER, OUTPUT);
  Timer1.initialize();
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(beep, beep_delay);

  // turn on lcd

  //lcd.init();
  //lcd.backlight();

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    //Serial.println(cmd);
    move();
  }
}

void move() {
  switch(cmd) {
    case 'w': w.forward(); reset_beeping(); break;
    case 'x': w.back(); set_beeping(); break;
    case 'a': w.forwardLeft(); reset_beeping(); break;
    case 'd': w.forwardRight(); reset_beeping(); break;
    case 'z': w.backLeft(); reset_beeping(); break;
    case 'c': w.backRight(); reset_beeping(); break;
    case 's': w.stop(); reset_beeping(); break;
    case '1': w.setSpeedLeft(75); reset_beeping(); break;
    case '2': w.setSpeedLeft(200); reset_beeping(); break;
    case '9': w.setSpeedRight(75); reset_beeping(); break;
    case '0': w.setSpeedRight(200); reset_beeping(); break;
    case '5': w.setSpeed(100); reset_beeping(); break;
    case 'f': distance = Serial.parseInt(SKIP_ALL); w.goForward(distance); reset_beeping(); break;
    case 'b': distance = Serial.parseInt(SKIP_ALL); w.goBack(distance); reset_beeping(); break;
  }
}

void reset_beeping() {
  beeping = false;
  digitalWrite(BEEPER, LOW);
}

void set_beeping() {
  beeping = true;
}

void beep() {
  if (beeping) {
    beep_state = digitalRead(BEEPER);
    digitalWrite(BEEPER, beep_state ^ 1);
  }
}
