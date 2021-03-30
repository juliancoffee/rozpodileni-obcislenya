#include <stdatomic.h>
#include <gtk/gtk.h>

void draw_square(cairo_t *cr, atomic_int *colors, size_t size);
