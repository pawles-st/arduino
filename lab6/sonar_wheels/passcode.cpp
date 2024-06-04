#include <Arduino.h>
#include <stdbool.h>

#include "passcode.h"

void input_passcode() {
  while (true) {
    int passcode = Serial.parseInt();
    if (passcode == BEGIN_CODE) {
      Serial.println("Code correct; starting now.");
      break;
    } else {
      Serial.println("CODE INCORRECT.");
    }
  }
} 
