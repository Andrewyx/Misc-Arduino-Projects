#include "io.h"
#include "arrows.h"
#include "avoider.h"
#include "breakout.h"
#include "pong.h"
#include "snake.h"

// (https://xantorohara.github.io/led-matrix-editor/)
// ----- Paste code from LED matrix editor below. -----
const uint64_t IMAGES[] = {
  0x0000000000000000,
  0x0080808000008000,
  0x0080808000008000,
  0x0040c0c00000c000,
  0x0040c0c00000c000,
  0x0020e0e00000e000,
  0x0020e0e00000e000,
  0x0090f0f08080f000,
  0x0090f0f08080f000,
  0x004878f8c0c07800,
  0x004878f8c0c07800,
  0x00243c7c60603c00,
  0x00121e3e30301e00,
  0x00121e3e30301e00,
  0x00121e3e30301e00,
  0x00925f003eb1301e,
  0xff6da0ffc14ecfe1,
  0x7b4320434140cf61,
  0x4100000100008041,
  0x0000000000000000,
  0x0000000000000000
};
const int IMAGES_LEN = sizeof(IMAGES)/8;

// ----- Paste code from LED matrix editor above. -----
// Below, you can change how fast the animation plays.
// The number describes how long to wait before displaying the next frame, in 1/60ths of a second.
const int frameDelay = 20;

#define MODE(name) {name##_setup, name##_loop}
#define NUM_MODES (sizeof(modes) / sizeof(*modes))
static struct {
  void (*setup)();
  void (*loop)();
} modes[] = {
  MODE(pong),
  MODE(avoider),
  MODE(snake),
  MODE(breakout),
  MODE(arrows)//,
  //MODE(tetris)
};

static struct {
  uint8_t index;
  uint8_t choosing : 1;
  uint8_t blink_count : 7;
} mode = {0, 1, 0};

void animate(const uint64_t *images, size_t length, int frames) {
  while (length) {
    screen = *images;
    screen = (screen & 0xFFFFFFFF00000000) >> 32 | (screen & 0x00000000FFFFFFFF) << 32;
    screen = (screen & 0xFFFF0000FFFF0000) >> 16 | (screen & 0x0000FFFF0000FFFF) << 16;
    screen = (screen & 0xFF00FF00FF00FF00) >> 8  | (screen & 0x00FF00FF00FF00FF) << 8;
    screen = (screen & 0xF0F0F0F0F0F0F0F0) >> 4  | (screen & 0x0F0F0F0F0F0F0F0F) << 4;
    screen = (screen & 0xCCCCCCCCCCCCCCCC) >> 2  | (screen & 0x3333333333333333) << 2;
    screen = (screen & 0xAAAAAAAAAAAAAAAA) >> 1  | (screen & 0x5555555555555555) << 1;
    for (int i = 0; i < frames; i++)
      render();
    images++;
    length--;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  screen = 0;
  animate(IMAGES, IMAGES_LEN, frameDelay);
}

void loop() {
  update_inputs();
  // Update choosing
  if (mode.choosing) {
    if (rise.right) {
      mode.choosing = 0;
      modes[mode.index].setup();
    }
  } else {
    if (inputs.up && inputs.down && inputs.left && inputs.right)
      mode.choosing = 1;
  }
  if (mode.choosing) {
    // Choosing code
    screen = draw_glyph(mode.index + 1);
    screen >>= 12;
    if (mode.index != 0) {
      if (mode.blink_count & 0b1000000)
        screen |= 0x40E0000000000000;
      if (rise.up) {
        mode.index--;
        mode.blink_count = 0x7F;
      }
    }
    if (mode.index != NUM_MODES - 1) {
      if (mode.blink_count & 0b1000000)
        screen |= 0x000000000000E040;
      if (rise.down) {
        mode.index++;
        mode.blink_count = 0x7F;
      }
    }
    mode.blink_count--;
  } else {
    // Run mode code
    modes[mode.index].loop();
  }
  render();
}
