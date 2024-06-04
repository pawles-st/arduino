#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Wheels.h"

#ifndef LCD_H
#define LCD_H

#define LCD_ADDRESS 0x27

#define ANIM_LENGTH 4
#define ENGINE_UP 4
#define ENGINE_DOWN 5
#define ENGINE_STOP 6
#define PERMISSION 7

enum Direction {
  UP,
  DOWN,
  OTHER,
};

class LCD {
  public:
    LCD();
    void clear();
    void init();
    void update_animation(EngineState right_state, EngineState left_state);
    void print_movement_info(float distance_left, EngineState right_state, EngineState left_state);
  private:
    LiquidCrystal_I2C lcd;
    int current_anim_char;
    Direction direction;
};

#endif
