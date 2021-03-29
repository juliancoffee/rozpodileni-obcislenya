#include <gtk/gtk.h>
#include "globals.h"
#include "util.h"
#include "draw.h"
#include "sets.h"

extern struct GlobalData global_data;

void on_draw_button(GtkWidget *_widget, gpointer drawing_area) {
  /* cairo context */
  cairo_t *cr;
  size_t pixels = global_data.pixels;

  /* Paint to the surface, where we store our state */
  cr = cairo_create (global_data.surface);

  int* colors = malloc(sizeof(int) * pixels * pixels);
  fill_mandelbrot(colors, pixels);
  draw_square(cr, colors, pixels);

  /* actually redraw */
  gtk_widget_queue_draw_area (drawing_area, 0, 0, pixels, pixels);
}
