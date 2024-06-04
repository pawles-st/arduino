#include "lcd.h"
#include "lcd_anim.h"

LCD::LCD() : lcd(LiquidCrystal_I2C(LCD_ADDRESS, 16, 2)), current_anim_char(0), direction(Direction::OTHER) {}

void LCD::init() {}

void LCD::clear() {}

void LCD::update_animation(EngineState right_state, EngineState left_state) {}

void LCD::print_movement_info(float distance_left, EngineState right_state, EngineState left_state) {}
