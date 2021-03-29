#include <complex.h>
#include "globals.h"
#include "util.h"

double norm(complex double z) {
  double x = creal(z);
  double y = cimag(z);
  return x * x + y * y;
}

size_t mandelbrot_cell(double x, double y, double pixels) {
    complex double Z = 0 + I * 0;
    complex double C = 2 * x/pixels - 1.5 + (2 * y/pixels - 1) * I;
    size_t iters = 0;
    while (norm(Z) < 4.0 && iters < NUM_COLORS - 1) {
      Z = cpow(Z, 2) + C;
      iters++;
    }
    return iters;
}

void fill_mandelbrot(int *colors, size_t pixels) {
  for (int y = 0; y < pixels; y++) {
    for (int x = 0; x < pixels; x++) {
    int* to_set = element_at(colors, x, y, pixels);
    *to_set = mandelbrot_cell(x, y, pixels);
    }
  }
}
