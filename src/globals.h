#include <gtk/gtk.h>
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

struct GlobalData {
  size_t pixels;
  struct Palette palette;
  cairo_surface_t *surface;
  int *set;
  bool is_sync;
  size_t num_threads;
};
