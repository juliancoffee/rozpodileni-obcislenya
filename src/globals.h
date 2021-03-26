#include <stdbool.h>
#include <stddef.h>
#include <gtk/gtk.h>

struct RGB {
  double red;
  double green;
  double blue;
};

struct Palette {
  struct RBG *data;
  size_t len;
};

struct GlobalData {
  size_t pixels;
  struct Palette palette;
  cairo_surface_t* surface;
};
