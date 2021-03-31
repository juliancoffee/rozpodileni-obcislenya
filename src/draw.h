#pragma once
#include "globals.h"
#include <gtk/gtk.h>
#include <stdatomic.h>

int draw_square(cairo_t *cr,
                atomic_int *colors,
                size_t size,
                struct palette_t palette_t);
