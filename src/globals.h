#pragma once
#include <gtk/gtk.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

#define NUM_COLORS 500

struct rgb_tuple_t {
  double red;
  double green;
  double blue;
};

struct palette_t {
  struct rgb_tuple_t *data;
  size_t len;
};

struct computation_context_t {
  size_t pixels;
  atomic_int *set;
  bool is_sync;
  size_t num_threads;
};

struct drawing_context_t {
  struct palette_t palette;
  cairo_surface_t *surface;
};

struct GlobalData {
  struct computation_context_t *comp_ctx;
  struct drawing_context_t *draw_ctx;
};

struct binded_widget_t {
  GtkWidget *widget;
  struct GlobalData *data;
};
