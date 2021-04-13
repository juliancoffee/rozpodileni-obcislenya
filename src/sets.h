#pragma once
#include "data.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

void fill_mandelbrot(
    atomic_int *colors,
    size_t pixels,
    bool use_priority,
    atomic_bool *is_paused,
    struct worker_t *workers,
    uint16_t num_threads);
