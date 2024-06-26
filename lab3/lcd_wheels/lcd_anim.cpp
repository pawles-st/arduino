#include <Arduino.h>

#include "lcd_anim.h"

uint8_t arrowUp0[8] =
{
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};
uint8_t arrowUp1[8] =
{
  0b10101,
  0b00100,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110
};
uint8_t arrowUp2[8] =
{
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b00100
};
uint8_t arrowUp3[8] =
{
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b00100,
  0b00100,
  0b00000
};
uint8_t arrowDown0[8] =
{
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100
};
uint8_t arrowDown1[8] =
{
  0b01110,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b10101
};
uint8_t arrowDown2[8] =
{
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00100
};
uint8_t arrowDown3[8] =
{
  0b00000,
  0b00100,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
uint8_t engineUp[8] =
{
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11011,
  0b10001,
  0b00000,
  0b00000
};
uint8_t engineDown[8] =
{
  0b00000,
  0b00000,
  0b10001,
  0b11011,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};
uint8_t engineStop[8] =
{
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};
uint8_t permission[8] =
{
  0b01110,
  0b11011,
  0b00011,
  0b01111,
  0b01110,
  0b00000,
  0b01110,
  0b01110
};

