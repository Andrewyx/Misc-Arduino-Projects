#include "avoider.h"
#include <Arduino.h>
#include <math.h>
#include "io.h"

enum mode {
  gameplay, wait_for_input
};

static enum mode mode;
static int8_t pos; // 0 = right, 7 = left
static uint8_t delay_left; // Frames until the next tick
static int8_t space_left; // Ticks until the next wall appears
static int32_t score;

void avoider_setup() {
  mode = gameplay;
  pos = 3;
  delay_left = 128;
  space_left = 1;
  score = -3;
  screen = 0x8181818181818181;
}

static void loop_gameplay() {
  // Erase old position
  screen &= ~(1 << pos);
  // Process controls
  if ((frame & 0b111) == 0) {
    if (inputs.left && !(screen & (1 << (pos + 1)))) {
      pos++;
    }
    if (inputs.right && !(screen & (1 << (pos - 1)))) {
      pos--;
    }
  }
  // Draw new position
  screen |= (1 << pos);
  // Drawing & logic
  if (--delay_left == 0) {
    delay_left = max(768 / sqrt(73.0 + score * 3.0) - 30, 1);
    screen >>= 8;
    screen |= 0x8100000000000000;
    if (--space_left == 0) {
      score++;
      space_left = 3;
      screen |= 0b1111ULL << (7 * 8 + rand() % 5);
    }
    // Check game over
    if (screen & (1 << pos)) {
      screen = draw_num(score);
      mode = wait_for_input;
      return;
    }
  }
}

static void loop_wait_for_input() {
  if (rise.up || rise.left || rise.right || rise.down) {
    // If any button pressed, proceed
    // Reset
    avoider_setup();
  }
}

void avoider_loop() {
  switch (mode) {
    case gameplay:
      loop_gameplay();
      break;
    case wait_for_input:
      loop_wait_for_input();
      break;
  }
}
