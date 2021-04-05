#include "controls.h"
#include "draw.h"
#include "data.h"
#include "message.h"
#include "sets.h"
#include "util.h"
#include <gtk/gtk.h>

void draw_button_cb(struct binded_widget_t *bind) {
  g_debug("DRAW\n");
  cairo_t *cr;
  struct computation_context_t *ctx = bind->data->comp_ctx;
  struct drawing_context_t *draw_ctx = bind->data->draw_ctx;
  GtkWidget *drawing_area = bind->widget;
  size_t pixels = ctx->pixels;
  bool is_sync = ctx->is_sync;

  /* Paint to the surface, where we store our state */
  cr = cairo_create(draw_ctx->surface);
  atomic_int *colors = ctx->set;
  draw_square(cr, colors, pixels, draw_ctx->palette);

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

void sync_button_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  ctx->is_sync = true;

  update_info(text_view, ctx);
}

void async_button_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  ctx->is_sync = false;

  update_info(text_view, ctx);
}

void increase_threads_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  size_t to_set = ctx->num_threads + 1;
  ctx->num_threads = to_set;

  update_info(text_view, ctx);
}

void decrease_threads_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  size_t to_set = ctx->num_threads - 1;
  if (to_set > 1) {
    ctx->num_threads = to_set;
  } else {
    ctx->num_threads = 1;
  }

  update_info(text_view, ctx);
}
