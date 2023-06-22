#ifndef LEDTENDO_IO_H
#define LEDTENDO_IO_H

#include <stdint.h>

extern uint64_t screen;
extern uint32_t frame;

struct inputs {
  uint8_t up : 1;
  uint8_t down : 1;
  uint8_t left : 1;
  uint8_t right : 1;
};

extern struct inputs inputs;
extern struct inputs prev;
extern struct inputs rise;
extern struct inputs fall;

void update_inputs();

void render();

uint64_t draw_num(uint64_t number);

uint64_t draw_glyph(uint8_t index);

#endif
