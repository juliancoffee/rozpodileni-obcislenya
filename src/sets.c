#include "sets.h"
#include "data.h"
#include "util.h"
#include <complex.h>

static double norm(complex double z) {
  double x = creal(z);
  double y = cimag(z);
  return x * x + y * y;
}

static size_t mandelbrot_cell(double x, double y, double pixels) {
  complex double Z = 0 + I * 0;
  complex double C = 2 * x / pixels - 1.5 + (2 * y / pixels - 1) * I;
  size_t iters = 0;
  while (norm(Z) < 4.0 && iters < NUM_COLORS - 1) {
    Z = cpow(Z, 2) + C;
    iters++;
  }
  return iters;
}

static void mandelbrot_fill_range(
    atomic_int *colors,
    size_t ystart,
    size_t yend,
    size_t pixels,
    atomic_bool *is_paused) {
  for (size_t y = ystart; y < yend; y++) {
    for (size_t x = 0; x < pixels; x++) {
      while (*is_paused == 1) {
        // pause, do nothing
      }
      atomic_int *to_set = element_at(colors, x, y, pixels);
      *to_set = mandelbrot_cell((double) x, (double) y, (double) pixels);
    }
  }
  g_debug("filled range [%zu, %zu)", ystart, yend);
}

static void *mandelbrot_fill_range_helper(void *arg) {
  struct packed_args_t *args = arg;
  mandelbrot_fill_range(
      args->colors, args->ystart, args->yend, args->pixels, args->is_paused);
  free(args);
  return NULL;
}

void fill_mandelbrot(
    atomic_int *colors,
    size_t pixels,
    atomic_bool *is_paused,
    struct worker_t *workers,
    uint16_t num_threads) {

  for (uint16_t n = 0; n < num_threads; n++) {
    size_t start = n * pixels / num_threads;
    size_t end = (n + 1) * pixels / num_threads;
    // memory management: freed in callback function
    struct packed_args_t args = {
        .colors = colors,
        .ystart = start,
        .yend = end,
        .pixels = pixels,
        .is_paused = is_paused,
    };
    pthread_create(
        &workers[n].thread, NULL, mandelbrot_fill_range_helper, BOXED(args));
    workers[n].is_init = true;
  }
}
