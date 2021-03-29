#include <complex.h>
#include "globals.h"
#include "util.h"

void fill_mandelbrot(int *colors, size_t pixels) {
  for (int x = 0; x < pixels; x++) {
    for (int y = 0; y < pixels; y++) {
    int* to_set = element_at(colors, x, y, pixels);
    *to_set = x % 500;
    }
  }
}
