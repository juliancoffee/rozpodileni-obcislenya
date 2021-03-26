#include "util.h"
#include <gtk/gtk.h>

// input: ratio is between 0 to 1
// output: rgb color
static void rgb(double ratio, double *red, double *green, double *blue) {
  // we want to normalize ratio so that it fits in to 6 regions
  // where each region is 256 units long
  int normalized = (int)(ratio * 256 * 6);

  // find the distance to the start of the closest region
  double x = (double)(normalized % 256) / 256;

  *red = 0;
  *green = 0;
  *blue = 0;
  switch (normalized / 256) {
  case 0:
    *red = 1;
    *green = x;
    *blue = 0;
    break; // red
  case 1:
    *red = 1 - x;
    *green = 1;
    *blue = 0;
    break; // yellow
  case 2:
    *red = 0;
    *green = 1;
    *blue = x;
    break; // green
  case 3:
    *red = 0;
    *green = 1 - x;
    *blue = 1;
    break; // cyan
  case 4:
    *red = x;
    *green = 0;
    *blue = 1;
    break; // blue
  case 5:
    *red = 1;
    *green = 0;
    *blue = 1 - x;
    break; // magenta
  }
}

//input: int color from 0 to 500
static void set_colors_from(int color, double *red, double *green,
                            double *blue) {
  double colorf = color;
  rgb(colorf / 500, red, green, blue);
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
