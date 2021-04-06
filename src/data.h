#pragma once
#include "memmacros.h"
#include <gtk/gtk.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

#define NUM_COLORS 500

struct rgb_tuple_t {
  double red;
  double green;
  double blue;
};

struct palette_t {
  struct rgb_tuple_t *data;
  size_t len;
};

struct computation_context_t {
  size_t pixels;
  atomic_int *set;
  bool is_sync;
  pthread_t *workers;
  atomic_bool *is_paused;
  size_t num_threads;
};

struct drawing_context_t {
  struct palette_t palette;
  cairo_surface_t *surface;
};

struct GlobalData {
  struct computation_context_t *comp_ctx;
  struct drawing_context_t *draw_ctx;
};

struct binded_widget_t {
  GtkWidget *widget;
  struct GlobalData *data;
};

struct packed_args_t {
  atomic_int *colors;
  atomic_bool *is_paused;
  size_t ystart;
  size_t yend;
  size_t pixels;
};

// template delcaration
DECLARE_BOXING_FOR(struct drawing_context_t, boxed_draw);
DECLARE_BOXING_FOR(struct computation_context_t, boxed_comp);
DECLARE_BOXING_FOR(struct packed_args_t, boxed_args);
DECLARE_BOXING_FOR(struct binded_widget_t, boxed_bind);
DECLARE_BOXING_FOR(atomic_bool, boxed_atomic_bool);

/* initialize value on the heap and return pointer to that value
 */
#define BOXED(value)                                                           \
  DISPATCH(                                                                    \
      value,                                                                   \
      MATCH(struct drawing_context_t, boxed_draw),                             \
      MATCH(struct computation_context_t, boxed_comp),                         \
      MATCH(struct binded_widget_t, boxed_bind),                               \
      MATCH(bool, boxed_atomic_bool),                                          \
      MATCH(struct packed_args_t, boxed_args))
