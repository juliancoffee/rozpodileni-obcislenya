#include "util.h"
#include <gtk/gtk.h>

static void set_colors_from(int color, double *red, double *green,
                            double *blue) {
  switch (color) {
  case 1:
    *red = 1;
    break;
  case 2:
    *green = 1;
    break;
  case 3:
    *blue = 1;
    break;
  }
}

void draw_square(cairo_t *cr, int *colors, size_t size) {
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      double red = 0;
      double green = 0;
      double blue = 0;
      int *color = get_at(colors, x, y, size);
      set_colors_from(*color, &red, &green, &blue);
      cairo_set_source_rgb(cr, red, green, blue);
      cairo_rectangle(cr, x, y, 1, 1);
      cairo_fill(cr);
    }
  }
  cairo_destroy(cr);
}
