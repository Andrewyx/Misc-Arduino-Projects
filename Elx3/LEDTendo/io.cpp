#include "io.h"
#include <Arduino.h>

#define ROW_ON HIGH
#define ROW_OFF LOW
#define COL_ON LOW
#define COL_OFF HIGH

#define PIN_UP A6
#define PIN_DOWN 10
#define PIN_LEFT A7
#define PIN_RIGHT 11

static const struct inputs empty_inputs = {0, 0, 0, 0};

static const uint8_t matrix_rows[] = { // bottom to top
//  6, 3, 8, 2, A3, 9, A5, 13, 0
  A1, A4, 13, A5, 6, 12, 4, 9, 0
};
static const uint8_t matrix_cols[] = { // right to left
//  A7, A6, A2, 7, A1, 5, 4, A4, 0
  2, 3, 7, A0, 8, A2, A3, 5, 0
};

uint64_t screen = 0;
uint32_t frame = 0;

struct inputs inputs = empty_inputs;
struct inputs prev = empty_inputs;
struct inputs rise = empty_inputs;
struct inputs fall = empty_inputs;

static inline void clear_inputs() {
  inputs = empty_inputs;
  prev = empty_inputs;
  rise = empty_inputs;
  fall = empty_inputs;
}

static inline void update_rise_fall() {
  rise.up = inputs.up & ~prev.up;
  rise.down = inputs.down & ~prev.down;
  rise.left = inputs.left & ~prev.left;
  rise.right = inputs.right & ~prev.right;
  fall.up = ~inputs.up & prev.up;
  fall.down = ~inputs.down & prev.down;
  fall.left = ~inputs.left & prev.left;
  fall.right = ~inputs.right & prev.right;
}

void update_inputs() {
  prev = inputs;
  inputs.up = analogRead(PIN_UP) > 511;
  inputs.down = digitalRead(PIN_DOWN);
  inputs.left = analogRead(PIN_LEFT) > 511;
  inputs.right = digitalRead(PIN_RIGHT);
  update_rise_fall();
}

void render() {
  uint64_t scr = screen;
  for (const uint8_t *row = matrix_rows; *row; row++) {
    digitalWrite(*row, ROW_ON);
    for (const uint8_t *col = matrix_cols; *col; col++) {
      digitalWrite(*col, (scr & 1) ? COL_ON : COL_OFF);
      scr >>= 1;
    }
    delayMicroseconds(790);
    digitalWrite(*row, ROW_OFF);
    for (const uint8_t *col = matrix_cols; *col; col++) {
      digitalWrite(*col, COL_OFF);
    }
    delayMicroseconds(250);
  }
  frame++;
}

static const uint64_t numbers[] = {
  0x40A0A0A040000000, // 0
  0x40C04040E0000000, // 1
  0xC0204080E0000000, // 2
  0xC0204020C0000000, // 3
  0x80A0E02020000000, // 4
  0xE080C020C0000000, // 5
  0x6080E0A0E0000000, // 6
  0xE020404040000000, // 7
  0xE0A0E0A0E0000000, // 8
  0xE0A0E020C0000000, // 9
  0x40A0E0A0A0000000, // A
  0xC0A0C0A0C0000000, // B
  0x6080808060000000, // C
  0xC0A0A0A0C0000000, // D
  0xE080C080E0000000, // E
  0xE080C08080000000 // F
};

uint64_t draw_num(uint64_t number) {
  if (number < 10) {
    return numbers[number] >> 5;
  } else {
    uint64_t scr = 0;
    uint8_t zeroes = 0;
    while (number >= 100) {
      zeroes++;
      if (number % 10 >= 5 && number < 1000) {
        number /= 10;
        number++;
      } else {
        number /= 10;
      }
    }
    while (zeroes --> 0) {
      scr <<= 1;
      scr |= 1;
    }
    scr |= numbers[number / 10];
    scr |= numbers[number % 10] >> 5;
    return scr;
  }
}

uint64_t draw_glyph(uint8_t id) {
  return numbers[id];
}
