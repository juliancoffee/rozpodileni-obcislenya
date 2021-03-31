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
  struct computation_context_t *ctx = global_data.comp_ctx;
  size_t pixels = ctx->pixels;
  bool is_sync = ctx->is_sync;

  /* Paint to the surface, where we store our state */
  cr = cairo_create(global_data.surface);
  atomic_int *colors = ctx->set;
  draw_square(cr, colors, pixels);

  /* Actually redraw */
  gtk_widget_queue_draw_area(drawing_area, 0, 0, pixels, pixels);

  /* Freeing resources */
  if (is_sync) {
    free(colors);
    ctx->set = NULL;
  }
}

void compute_button_cb(struct computation_context_t *ctx) {
  g_debug("CALCULATE\n");

  size_t pixels = ctx->pixels;
  size_t num_threads = ctx->num_threads;
  bool is_sync = ctx->is_sync;

  atomic_int *set = calloc(pixels * pixels, sizeof(atomic_int));
  ctx->set = set;

  fill_mandelbrot(set, pixels, is_sync, num_threads);
}

void sync_button_cb(GtkWidget *text_view) {
  global_data.comp_ctx->is_sync = true;
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) text_view);
  char *msg = info_text();
  gtk_text_buffer_set_text(buf, msg, -1);
  free(msg);
}

void async_button_cb(GtkWidget *text_view) {
  global_data.comp_ctx->is_sync = false;
  GtkTextBuffer *buf = gtk_text_view_get_buffer((GtkTextView *) text_view);
  char *msg = info_text();
  gtk_text_buffer_set_text(buf, msg, -1);
  free(msg);
}
