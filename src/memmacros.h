#include "data.h"
#include "util.h"
#include <assert.h>

// trick to force semicolon on the callside
#define FORCE_SEMICOLON() static_assert(true, "")

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

#define MATCH(T, target)                                                       \
  T:                                                                           \
  target

#define DISPATCH(value, ...) _Generic((value), __VA_ARGS__)(value)

#define BOXED(value)                                                           \
  DISPATCH(value,                                                              \
           MATCH(struct drawing_context_t, boxed_draw),                        \
           MATCH(struct computation_context_t, boxed_comp))
