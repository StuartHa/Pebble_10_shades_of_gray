#include <pebble.h>

// Values for halftones taken from http://www.ee.ryerson.ca/~courses/ee8202/Labs/Lab-1-new.html
static bool halftones[10][3][3] = {
  {{0,0,0},
   {0,0,0},
   {0,0,0}},

  {{0,0,0},
   {0,1,0},
   {0,0,0}},

  {{0,0,0},
   {1,1,0},
   {0,0,0}},

  {{0,0,0},
   {1,1,0},
   {0,1,0}},

  {{0,0,0},
   {1,1,1},
   {0,1,0}},

  {{0,0,1},
   {1,1,1},
   {0,1,0}},

  {{0,0,1},
   {1,1,1},
   {1,1,0}},

  {{1,0,1},
   {1,1,1},
   {1,1,0}},

  {{1,0,1},
   {1,1,1},
   {1,1,1}},

  {{1,1,1},
   {1,1,1},
   {1,1,1}}
};

void fill_dithered_rect(GContext *ctx, GRect rect, int level) {
  for (int i = rect.origin.x; i < rect.origin.x + rect.size.w; i++) {
    for (int j = rect.origin.y; j < rect.origin.y + rect.size.h; j++) {
      bool black = halftones[level][i % 3][j % 3];
      if (black) {
        graphics_draw_pixel(ctx, (GPoint) {i, j});
      }
    }
  }
}
