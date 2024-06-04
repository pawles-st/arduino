#include "lcd.h"
#include "lcd_anim.h"

LCD::LCD() : lcd(LiquidCrystal_I2C(LCD_ADDRESS, 16, 2)), current_anim_char(0), direction(Direction::OTHER) {}

void LCD::init() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(ENGINE_UP, engineUp);
  lcd.createChar(ENGINE_DOWN, engineDown);
  lcd.createChar(ENGINE_STOP, engineStop);
  lcd.createChar(PERMISSION, permission);
}

void LCD::clear() {
  lcd.clear();
}

void LCD::update_animation(EngineState right_state, EngineState left_state) {
  if (this->direction != Direction::UP && right_state == EngineState::FORWARD && left_state == EngineState::FORWARD) {

    // both wheels are moving forward -> the car is going forward

    this->direction = Direction::UP;

    // create forward animation set

    lcd.createChar(0, arrowUp0);
    lcd.createChar(1, arrowUp1);
    lcd.createChar(2, arrowUp2);
    lcd.createChar(3, arrowUp3);

  } else if (this->direction != Direction::DOWN && right_state == EngineState::BACKWARD && left_state == EngineState::BACKWARD) {

    // both wheels are moving backward -> the car is going backward

    this->direction = Direction::DOWN;

    // create backward animation set

    lcd.createChar(0, arrowDown0);
    lcd.createChar(1, arrowDown1);
    lcd.createChar(2, arrowDown2);
    lcd.createChar(3, arrowDown3);

  } else {

    // reset direction

    this->direction = Direction::OTHER;
  }
}

void LCD::print_movement_info(float distance_left, EngineState right_state, EngineState left_state) {

  // convert distance to string representation

  char distance_str[16];
  dtostrf(distance_left, 2, 1, distance_str);

  if (distance_left > 0) {

    // print distance on lcd

    lcd.setCursor(0, 0);
    lcd.print(distance_str);

  }

  // print engines' states

  lcd.setCursor(15, 1);
  switch (right_state) {
    case EngineState::FORWARD: lcd.write(ENGINE_UP); break;
    case EngineState::BACKWARD: lcd.write(ENGINE_DOWN); break;
    case EngineState::STOP: lcd.write(ENGINE_STOP); break;
  }

  lcd.setCursor(0, 1);
  switch (left_state) {
    case EngineState::FORWARD: lcd.write(ENGINE_UP); break;
    case EngineState::BACKWARD: lcd.write(ENGINE_DOWN); break;
    case EngineState::STOP: lcd.write(ENGINE_STOP); break;
  }

  // print movement animation

  lcd.setCursor(6, 1);
  lcd.write(this->current_anim_char);
  lcd.setCursor(7, 1);
  lcd.write(this->current_anim_char);
  lcd.setCursor(8, 1);
  lcd.write(this->current_anim_char);
  lcd.setCursor(9, 1);
  lcd.write(this->current_anim_char);

  // update animation frame

  if (this->direction == Direction::UP || this->direction == Direction::DOWN) {
    this->current_anim_char = (this->current_anim_char + 1) % ANIM_LENGTH;
  } else {
    this->current_anim_char = 0;
  }
}