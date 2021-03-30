#include "globals.h"
#include "util.h"
#include <complex.h>

extern struct GlobalData global_data;

struct PackedArgs {
  atomic_int *colors;
  size_t ystart;
  size_t yend;
  size_t pixels;
};

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

static void mandelbrot_fill_range(atomic_int *colors, size_t ystart, size_t yend,
                                  size_t pixels) {
  printf("ystart: %zu\n", ystart);
  for (int y = ystart; y < yend; y++) {
    for (int x = 0; x < pixels; x++) {
      atomic_int *to_set = element_at(colors, x, y, pixels);
      *to_set = mandelbrot_cell(x, y, pixels);
    }
  }
}

static void *mandelbrot_fill_range_helper(void *arg) {
  struct PackedArgs *args = arg;
  mandelbrot_fill_range(args->colors, args->ystart, args->yend, args->pixels);
  free(args);
  return NULL;
}

void fill_mandelbrot(atomic_int *colors, size_t pixels) {
  pthread_t *thread_ids = malloc(sizeof(pthread_t) * global_data.num_threads);
  for (int n = 0; n < global_data.num_threads; n++) {
    size_t start = n * pixels / global_data.num_threads;
    size_t end = (n + 1) * pixels / global_data.num_threads;
    printf("start: %zu\n", start);
    struct PackedArgs *args = malloc(sizeof(struct PackedArgs));
    args->colors = colors;
    args->ystart = start;
    args->yend = end;
    args->pixels = pixels;
    pthread_create(&thread_ids[n], NULL, mandelbrot_fill_range_helper, args);
  }
  if (global_data.is_sync) {
    for (int n = 0; n < global_data.num_threads; n++) {
      int res = pthread_join(thread_ids[n], NULL);
      printf("join result: %d\n", res);
    }
  }
  free(thread_ids);
}
