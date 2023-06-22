#include "snake.h"
#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define DELAY 30
#define EMPTY 0
#define SNAKE_UP 1
#define SNAKE_DOWN 2
#define SNAKE_LEFT 3
#define SNAKE_RIGHT 4

enum mode {
  gameplay, wait_for_input
};

struct point {
  int8_t x;
  int8_t y;
};

static enum mode mode;
static uint8_t delay_left;
static uint8_t num_spaces;
static uint8_t data[64];
static struct point head;
static struct point tail;
static uint8_t food_pos;
static uint8_t score;

static void generate_food() {
  uint8_t pos = (uint8_t) (rand() % num_spaces);
  uint8_t *d = data;
  while (1) {
    if (*d == EMPTY && pos-- == 0)
      break;
    d++;
  }
  food_pos = d - data;
}

void snake_setup() {
  mode = gameplay;
  // Clear data
  memset(data, 0, sizeof(data));
  // Add snake
  num_spaces = 64-3;
  data[24] = SNAKE_RIGHT;
  data[25] = SNAKE_RIGHT;
  data[26] = SNAKE_RIGHT;
  head = {2, 3};
  tail = {0, 3};
  score = 0;
  delay_left = DELAY;
  generate_food();
  screen = 0x000000E000000000;
}

static void lose() {
  screen = draw_num(score) >> 8;
  mode = wait_for_input;
}

static inline bool move_pos(struct point *pos) {
  uint8_t value = data[pos->y * 8 + pos->x];
  switch (value) {
    case SNAKE_UP:
      return --pos->y < 0;
    case SNAKE_DOWN:
      return ++pos->y > 7;
    case SNAKE_LEFT:
      return --pos->x < 0;
    case SNAKE_RIGHT:
      return ++pos->x > 7;
    default:
      return true;
  }
}

static void loop_gameplay() {
  uint8_t head_pos = head.y * 8 + head.x;
  // Get inputs
  if (rise.up)
    data[head_pos] = SNAKE_UP;
  if (rise.down)
    data[head_pos] = SNAKE_DOWN;
  if (rise.left)
    data[head_pos] = SNAKE_LEFT;
  if (rise.right)
    data[head_pos] = SNAKE_RIGHT;
  if (--delay_left == 0) {
    delay_left = DELAY;
    uint8_t value = data[head_pos];
    if (move_pos(&head)) {
      lose();
      return;
    }
    head_pos = head.y * 8 + head.x;
    screen |= 1ULL << (63 - head_pos);
    bool should_shrink = true;
    switch (data[head_pos]) {
      case EMPTY:
        data[head_pos] = value;
        break;
      default:
        // Whoops, snake crashed into itself
        lose();
        return;
    }
    // Process food
    if (head_pos == food_pos) {
      should_shrink = false;
      num_spaces--;
      score++;
      generate_food();
    }
    // Process tail
    if (should_shrink) {
      uint8_t tail_pos = tail.y * 8 + tail.x;
      // Erase tail
      screen &= ~(1ULL << (63 - tail_pos));
      // Advance tail
      move_pos(&tail);
      data[tail_pos] = EMPTY;
    }
    // Draw food
    screen |= 1ULL << (63 - food_pos);
  } else if (delay_left == DELAY / 2) {
    // Erase food
    screen &= ~(1ULL << (63 - food_pos));
  }
}

static void loop_wait_for_input() {
  if (rise.up || rise.left || rise.right || rise.down) {
    // If any button pressed, proceed
    snake_setup();
  }
}

void snake_loop() {
  switch (mode) {
    case gameplay:
      loop_gameplay();
      break;
    case wait_for_input:
      loop_wait_for_input();
      break;
  }
}

