#pragma once
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

void fill_mandelbrot(
    atomic_int *colors,
    size_t pixels,
    atomic_bool *is_paused,
    pthread_t *workers,
    size_t num_threads);
