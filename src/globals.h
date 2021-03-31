#pragma once
#include <gtk/gtk.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

#define NUM_COLORS 500

struct RGB {
  double red;
  double green;
  double blue;
};

struct Palette {
  struct RGB *data;
  size_t len;
};

struct computation_context_t {
  size_t pixels;
  atomic_int *set;
  bool is_sync;
  size_t num_threads;
};

struct GlobalData {
  struct computation_context_t *comp_ctx;
  struct Palette palette;
  cairo_surface_t *surface;
};
