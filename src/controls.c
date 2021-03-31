#include "controls.h"
#include "draw.h"
#include "globals.h"
#include "message.h"
#include "sets.h"
#include "util.h"
#include <gtk/gtk.h>

extern struct GlobalData global_data;

void draw_button_cb(GtkWidget *drawing_area) {
  cairo_t *cr;
  size_t pixels = global_data.pixels;

  /* Paint to the surface, where we store our state */
  cr = cairo_create(global_data.surface);
  atomic_int *colors = global_data.set;
  draw_square(cr, colors, pixels);

  /* Actually redraw */
  gtk_widget_queue_draw_area(drawing_area, 0, 0, pixels, pixels);

  /* Freeing resources */
  if (global_data.is_sync) {
    free(colors);
    global_data.set = NULL;
  }
}

void calculate_button_cb(gpointer _data) {
  (void) _data;
  g_message("CALCULATE\n");
  size_t pixels = global_data.pixels;
  atomic_int *set = calloc(pixels * pixels, sizeof(atomic_int));
  global_data.set = set;
  fill_mandelbrot(set, pixels, global_data.is_sync, global_data.num_threads);
}

void sync_button_cb(GtkWidget *text_view) {
  global_data.is_sync = true;
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) text_view);
  char *msg = info_text();
  gtk_text_buffer_set_text(buf, msg, -1);
  free(msg);
}

void async_button_cb(GtkWidget *text_view) {
  global_data.is_sync = false;
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) text_view);
  char *msg = info_text();
  gtk_text_buffer_set_text(buf, msg, -1);
  free(msg);
}
