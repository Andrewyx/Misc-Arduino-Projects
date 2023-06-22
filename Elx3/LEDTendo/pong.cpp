#include "pong.h"
#include "io.h"

#define DEFAULT_DELAY 30
#define START_DELAY 128
#define PADDLE_WIDTH 3
#define PADDLE_LEFT 0x8080800000000000
#define PADDLE_RIGHT 0x0101010000000000
#define WIN_A 0x000A4AC0510E0000
#define WIN_B 0x005052038A700000

enum mode {
  gameplay, wait_for_input
};

static enum mode mode;
static uint8_t delay_left;
static uint8_t delay_value;
static struct {
  uint8_t a : 4;
  uint8_t b : 4;
} paddles;
static struct {
  int8_t x;
  int8_t y;
  int8_t dx : 4;
  int8_t dy : 4;
} ball;
static struct {
  uint8_t a : 4;
  uint8_t b : 4;
} scores;

void pong_setup() {
  mode = gameplay;
  delay_left = 0;
  delay_value = DEFAULT_DELAY;
  paddles = {0, 8 - PADDLE_WIDTH};
  ball = {1, 1, 1, 1};
  scores = {0, 0};
}

static void loop_wait_for_input() {
  if (rise.up || rise.left || rise.right || rise.down) {
    // If any button pressed, proceed
    mode = gameplay;
    delay_left = 0;
    delay_value = DEFAULT_DELAY;
  }
}

static void show_score() {
  if (scores.a > 9) {
    screen = WIN_A;
    scores = {0, 0};
  } else if (scores.b > 9) {
    screen = WIN_B;
    scores = {0, 0};
  } else {
    screen = draw_glyph(scores.a);
    screen |= draw_glyph(scores.b) >> 5;
    screen >>= 8;
  }
  mode = wait_for_input;
}

static void loop_gameplay() {
  register int should_rerender = 0;
  // Get inputs
  if (rise.up && paddles.a != 0) {
    paddles.a--;
    should_rerender = 1;
  }
  if (rise.down && paddles.a != 8 - PADDLE_WIDTH) {
    paddles.a++;
    should_rerender = 1;
  }
  if (rise.left && paddles.b != 0) {
    paddles.b--;
    should_rerender = 1;
  }
  if (rise.right && paddles.b != 8 - PADDLE_WIDTH) {
    paddles.b++;
    should_rerender = 1;
  }
  // Decrement delay
  if (delay_left) {
    delay_left--;
  } else {
    // Do ball physics
    delay_left = delay_value;
    int8_t nx = ball.x + ball.dx;
    int8_t ny = ball.y + ball.dy;
    if (nx < 0) {
      // B won
      ball.x = 0; ball.y = paddles.a;
      ball.dx = 1, ball.dy = 1;
      scores.b++;
      show_score();
      mode = wait_for_input;
    } else if (nx > 7) {
      // A won
      ball.x = 7; ball.y = paddles.b;
      ball.dx = -1, ball.dy = 1;
      scores.a++;
      show_score();
      mode = wait_for_input;
    } else {
      if (ny < 0 || ny > 7) {
        ball.dy = -ball.dy;
        ny = ball.y + ball.dy;
      }
      if (nx == 0) {
        // might hit paddle A
        if ((paddles.a <= ny && ny < paddles.a + PADDLE_WIDTH) ||
            (paddles.a <= ball.y && ball.y < paddles.a + PADDLE_WIDTH)) {
          ball.dx = -ball.dx;
          nx = ball.x + ball.dx;
          delay_value--;
        }
      } else if (nx == 7) {
        // might hit paddle B
        if ((paddles.b <= ny && ny < paddles.b + PADDLE_WIDTH) ||
            (paddles.b <= ball.y && ball.y < paddles.b + PADDLE_WIDTH)) {
          ball.dx = -ball.dx;
          nx = ball.x + ball.dx;
          delay_value--;
        }
      }
      ball.x = nx;
      ball.y = ny;
      should_rerender = 1;
    }
  }
  if (should_rerender) {
    screen = PADDLE_LEFT >> (8 * paddles.a);
    screen |= PADDLE_RIGHT >> (8 * paddles.b);
    screen |= (1ULL << 63) >> (8 * ball.y + ball.x);
  }
}

void pong_loop() {
  switch (mode) {
    case gameplay:
      loop_gameplay();
      break;
    case wait_for_input:
      loop_wait_for_input();
      break;
  }
}
