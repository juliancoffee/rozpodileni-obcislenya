#include "controls.h"
#include "data.h"
#include "draw.h"
#include "message.h"
#include "sets.h"
#include <gtk/gtk.h>

void draw_button_cb(struct binded_widget_pair_t *bind) {
  g_debug("DRAW\n");
  cairo_t *cr;
  struct computation_context_t *ctx = bind->data->comp_ctx;
  struct drawing_context_t *draw_ctx = bind->data->draw_ctx;
  GtkWidget *drawing_area = bind->first;
  GtkWidget *error_view = bind->second;
  size_t pixels = ctx->pixels;
  uint16_t num_threads = ctx->num_threads;
  bool is_sync = ctx->is_sync;
  bool is_paused = *ctx->is_paused;

  // Waiting for computation to finish if synced
  if (is_sync) {
    if (is_paused) {
      // there will be deadlock if we start to wait for paused threads
      show_error(error_view, "Threads are pausing so we'll be waiting forever");
      return;
    }
    for (uint16_t n = 0; n < num_threads; n++) {
      if (ctx->workers[n].is_init == true) {
        pthread_join(ctx->workers[n].thread, NULL);
      }
    }
  }

  /* Paint to the surface, where we store our state */
  cr = cairo_create(draw_ctx->surface);
  atomic_int *colors = ctx->set;
  draw_square(cr, colors, pixels, draw_ctx->palette);

  /* Actually redraw */
  gtk_widget_queue_draw_area(drawing_area, 0, 0, pixels, pixels);
}

void compute_button_cb(struct computation_context_t *ctx) {
  g_debug("CALCULATE\n");

  size_t pixels = ctx->pixels;
  uint16_t num_threads = ctx->num_threads;

  atomic_int *set =
      calloc_or_die(pixels * pixels, sizeof(atomic_int), "allocating set");
  ctx->set = set;

  fill_mandelbrot(set, pixels, ctx->is_paused, ctx->workers, num_threads);
}

void toggle_pause_button_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  *ctx->is_paused = !(*ctx->is_paused);
  update_info(text_view, ctx);
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

void update_workers(
    struct computation_context_t *ctx, bool increase, GtkWidget *text_view) {

  uint16_t old_num = ctx->num_threads;
  /* update number of threads */
  uint16_t to_set;
  if (increase) {
    if (old_num == UINT16_MAX) {
      // it's time to stop increasing
      return;
    } else {
      to_set = old_num + 1;
    }
  } else {
    if (old_num == 1) {
      // it's time to stop decreasing
      return;
    } else {
      to_set = old_num - 1;
    }
  }
  ctx->num_threads = to_set;

  /* realloc workers */
  struct worker_t *new_workers = realloc_or_die(
      ctx->workers, to_set * sizeof(struct worker_t), "reallocating workers");
  ctx->workers = new_workers;

  /* partly initalize new workers */
  for (uint16_t n = old_num; n < to_set; n++) {
    ctx->workers[n].is_init = false;
  }

  update_info(text_view, ctx);
}

void increase_threads_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  update_workers(ctx, true, text_view);
}

void decrease_threads_cb(struct binded_widget_t *bind) {
  GtkWidget *text_view = bind->widget;
  struct computation_context_t *ctx = bind->data->comp_ctx;

  update_workers(ctx, false, text_view);
}
