#include "arrows.h"
#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>
#include "io.h"

#define BACKWARDS_CHANCE 3

enum mode {
  gameplay, wait_for_input, wait_one_frame
};

struct arrow {
  uint8_t backwards : 1; // Whether or not the arrow is drawn backwards
  uint8_t direction : 2; // The expected direction to be pressed -- 0=up, 1=right, 2=down, 3=left
};

static enum mode mode;
static struct arrow arrow;
static uint16_t score;

static inline void random_arrow() {
  struct arrow newarr;
  do {
    newarr.backwards = (random() % BACKWARDS_CHANCE) == 0;
    newarr.direction = random() % 4;
  } while (newarr.backwards == arrow.backwards && newarr.direction == arrow.direction);
  arrow = newarr;
}

static inline void draw_arrow() {
  switch (arrow.direction) {
    case 0: // up
      screen = arrow.backwards ? 0x3C242424E7422418 : 0x183C7EFF3C3C3C3C;
      break;
    case 1: // right
      screen = arrow.backwards ? 0x10305F81815F3010 : 0x080CFEFFFFFE0C08;
      break;
    case 2: // down
      screen = arrow.backwards ? 0x182442E72424243C : 0x3C3C3C3CFF7E3C18;
      break;
    case 3: // left
      screen = arrow.backwards ? 0x080CFA8181FA0C08 : 0x10307FFFFF7F3010;
      break;
  }
}

void arrows_setup() {
  mode = wait_one_frame;
  random_arrow();
  score = 0;
  draw_arrow();
}

static void loop_wait_for_input() {
  if (rise.up || rise.left || rise.right || rise.down) {
    // If any button pressed, proceed
    arrows_setup();
  }
}

static void loop_wait_one_frame() {
  mode = gameplay;
}

static void loop_gameplay() {
  uint8_t sum = rise.up + rise.down + rise.left + rise.right;
  if (sum == 0) return;
  if (sum > 1) goto lose;
  if ((arrow.direction == 0 && rise.up) ||
      (arrow.direction == 1 && rise.right) ||
      (arrow.direction == 2 && rise.down) ||
      (arrow.direction == 3 && rise.left)) {
    // Correct button pressed
    score++;
    random_arrow();
    draw_arrow();
    return;
  }
  lose:
  screen = draw_num(score);
  mode = wait_for_input;
}

void arrows_loop() {
  switch (mode) {
    case gameplay:
      loop_gameplay();
      break;
    case wait_for_input:
      loop_wait_for_input();
      break;
    case wait_one_frame:
      loop_wait_one_frame();
      break;
  }
}

