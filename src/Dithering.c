#include <pebble.h>
#include "DitherRect.h"

static Window *window;
static Layer *root_layer;
static int level;
static bool level_increasing = true;


static void draw_dither_timer(void *data) {
  if (level == 0 && !level_increasing) {
    level_increasing = true;
  } else if (level == 9 && level_increasing) {
    level_increasing = false;
  }
  level += (level_increasing) ? 1 : -1;

  layer_mark_dirty(root_layer);
  app_timer_register(100, draw_dither_timer, NULL);
}

static void update_proc(Layer *layer, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(0, 0, 144, 168), 0, GCornerNone);
  
  fill_dithered_rect(ctx, GRect(0, 0, 144, 168), level);
}

static void window_load(Window *window) {
  root_layer = window_get_root_layer(window);
  layer_set_update_proc(root_layer, update_proc);
  app_timer_register(100, draw_dither_timer, NULL);
}

static void init(void) {
  window = window_create();
  window_set_fullscreen(window, true);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
  });
  window_stack_push(window, true);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
