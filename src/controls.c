#include "draw.h"
#include "globals.h"
#include "sets.h"
#include "util.h"
#include <gtk/gtk.h>

extern struct GlobalData global_data;

void draw_button_cb(GtkWidget *drawing_area) {
  cairo_t *cr;
  size_t pixels = global_data.pixels;

  /* Paint to the surface, where we store our state */
  cr = cairo_create(global_data.surface);
  int *colors = global_data.set;
  draw_square(cr, colors, pixels);

  /* Actually redraw */
  gtk_widget_queue_draw_area(drawing_area, 0, 0, pixels, pixels);

  /* Freeing resources */
  if (global_data.is_sync) {
    free(colors);
    global_data.set = NULL;
  }
  // TODO: figure out what to do with this in async scenario
  // if we are freeing this memory at the time fill_mandelbrot is working
  // it will be undefined behaviour (and most probably SEGFAULT)
}

void calculate_button_cb(gpointer _data) {
  g_message("CALCULATE\n");
  size_t pixels = global_data.pixels;
  int *set = calloc(pixels * pixels, sizeof(int));
  global_data.set = set;
  fill_mandelbrot(set, pixels);
}

void sync_button_cb(gpointer _data) { global_data.is_sync = true; }
void async_button_cb(gpointer _data) { global_data.is_sync = false; }
