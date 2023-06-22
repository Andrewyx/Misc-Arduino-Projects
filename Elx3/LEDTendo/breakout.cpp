#include "breakout.h"
#include <Arduino.h>
#include "io.h"

#define DELAY 12
#define WAIT 64

enum mode {
  gameplay, wait_for_input
};

static enum mode mode;
static uint8_t delay_left;
static uint8_t wait_left;
static uint8_t score;
static int8_t paddle;
static struct {
  int8_t x;
  int8_t y;
  int8_t dx : 4;
  int8_t dy : 4;
} ball;

void breakout_setup() {
  mode = gameplay;
  delay_left = DELAY;
  wait_left = WAIT;
  score = 0;
  screen = 0xFFFF000000000000;
  paddle = 2;
  ball = {3, 6, 1, -1};
}

static void loop_wait_for_input() {
  if (rise.up || rise.left || rise.right || rise.down) {
    // If any button pressed, proceed
    breakout_setup();
  }
}

static void loop_gameplay() {
  // Process controls
  // Erase paddle
  screen &= 0xFFFFFFFFFFFFFF00;
  if (rise.left && paddle != 0)
    paddle--;
  if (rise.right && paddle != 8 - 3)
    paddle++;
  // Redraw paddle
  screen |= 0x00000000000000E0 >> paddle;
  // Check delay
  if (delay_left != 0) {
    delay_left--;
    return;
  }
  delay_left = DELAY;
  // Ball logic
  // Erase ball
  screen &= ~(1ULL << (63 - (ball.y * 8 + ball.x)));
  // Move ball
  if (ball.y == 0)
    ball.dy = -ball.dy;
  if (ball.y == 6) {
    score++;
    // Paddle hitting logic
    switch (ball.x - paddle) {
      case 1: // centre
        ball.x += ball.dx; // add an additional dx to switch parity
        ball.dx = 0; ball.dy = -1;
        break;
      case 0: // left
        if (ball.dx == 1) {
          ball.x++;
          ball.dx = 0;
        } else {
          ball.dx = -1;
        }
        ball.dy = -1;
        break;
      case 2: // right
        if (ball.dx == -1) {
          ball.x--;
          ball.dx = 0;
        } else {
          ball.dx = 1;
        }
        ball.dy = -1;
        break;
      case -1: // left-left
        if (ball.dx > 0) { ball.dx = -1; ball.dy = -1; }
        break;
      case 3: // right-right
        if (ball.dx < 0) { ball.dx = 1; ball.dy = -1; }
        break;
      default:
        break;
    }
  }
  if (ball.x == 0 || ball.x == 7)
    ball.dx = -ball.dx;
  // Check fall
  if (--wait_left == 0) {
    wait_left = WAIT;
    // Fall
    screen >>= 8;
    screen |= 0xFF00000000000000;
    if (screen & 0xFF) {
      // You lose
      screen = draw_num(score);
      mode = wait_for_input;
      return;
    }
    // Redraw paddle
    screen |= 0x00000000000000E0 >> paddle;
  }
  ball.x += ball.dx;
  ball.y += ball.dy;
  // Check lose
  if (ball.y >= 8) {
    // You lose
    screen = draw_num(score);
    mode = wait_for_input;
    return;
  }
  // Redraw ball
  screen |= 1ULL << (63 - (ball.y * 8 + ball.x));
}

void breakout_loop() {
  switch (mode) {
    case gameplay:
      loop_gameplay();
      break;
    case wait_for_input:
      loop_wait_for_input();
      break;
  }
}

