#pragma once
#include "data.h"
#include <assert.h>
#include <stdatomic.h>
#include <stddef.h>

// trick to force semicolon on the callside
#define FORCE_SEMICOLON() static_assert(true, "")

// memory management: caller owns the data
#define NEW(type) malloc(sizeof(type))

// memory management: caller owns the data
#define CREATE_BOXING_FOR(type, fn)                                            \
  inline type *fn(type value) {                                                \
    type *boxed = NEW(type);                                                   \
    *boxed = value;                                                            \
    return boxed;                                                              \
  }                                                                            \
  FORCE_SEMICOLON()

// template instantiation
CREATE_BOXING_FOR(struct drawing_context_t, boxed_draw);
CREATE_BOXING_FOR(struct computation_context_t, boxed_comp);

// argument dispatch
/* clang-format off */
#define BOXED(value)                                                           \
  _Generic((value), struct drawing_context_t     : boxed_draw,                 \
                    struct computation_context_t : boxed_comp                  \
)(value)
/* clang-format on */

atomic_int *element_at(atomic_int *matrix, size_t i, size_t j, size_t size);
