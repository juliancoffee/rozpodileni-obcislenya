#pragma once
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

void fill_mandelbrot(
    atomic_int *colors, size_t pixels, bool is_sync, size_t num_threads);
