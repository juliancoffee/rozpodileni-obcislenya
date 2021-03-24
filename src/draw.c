#include <gtk/gtk.h>

void draw_square(cairo_t* cr, int* colors, size_t size) {
  for (int x = 0; x < size; x++) {
    for (int y = 0; y < size; y++) {
      cairo_rectangle (cr, x, y, 1, 1);
    }
  }
  cairo_fill (cr);

  cairo_destroy (cr);
}
