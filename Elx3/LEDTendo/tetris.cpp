#include "tetris.h"
#include <stdlib.h>
#include "io.h"

struct piece {
  uint16_t data[4];
  uint8_t width : 4;
  uint8_t height : 4;
};

static inline uint64_t piece_rotation(const struct piece *pc, uint8_t rotation) {
  uint64_t raw = (uint64_t) pc->data[rotation];
  return ((raw & 0xF000) << (64 - 16))
       | ((raw & 0x0F00) << (64 - 12))
       | ((raw & 0x00F0) << (64 - 8))
       | ((raw & 0x000F) << (64 - 4));
}

#define PIECES_LEN (sizeof(PIECES) / sizeof(*PIECES))
const struct piece PIECES[] = {
  {0x8888, 0xF000, 0x8888, 0xF000, 1, 4}, // I-block
  {0x8E00, 0xC880, 0xE200, 0x44C0, 3, 2}, // J-block
  {0x2E00, 0x88C0, 0xE800, 0xC440, 3, 2}, // L-block
  {0xCC00, 0xCC00, 0xCC00, 0xCC00, 2, 2}, // O-block
  {0x6C00, 0x8C40, 0x6C00, 0x8C40, 3, 2}, // S-block
  {0x4E00, 0x8C80, 0xE400, 0x4C40, 3, 2}, // T-block
  {0xC600, 0x4C80, 0xC600, 0x4C80, 3, 2}  // Z-block
};

struct {
  const struct piece *type;
  uint8_t rotation : 2;
  int8_t x : 6;
  int8_t y;
} piece;

static inline const struct piece *random_piece() {
  return &PIECES[random() % 7];
}

static void init_piece() {
  piece.type = random_piece();
  piece.rotation = 0;
  //piece.x = //TODO
}

void tetris_setup() {
  screen = 0;
}

