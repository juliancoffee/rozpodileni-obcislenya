#pragma once
#include "data.h"
#include <stdatomic.h>
#include <stddef.h>

// memory management: caller owns the data
#define NEW(type) malloc(sizeof(type))

atomic_int *element_at(atomic_int *matrix, size_t i, size_t j, size_t size);
