#include <assert.h>

// memory management: caller owns the data
#define NEW(type) malloc(sizeof(type))

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


#define MATCH(T, target)                                                       \
  T:                                                                           \
  target

#define DISPATCH(value, ...) _Generic((value), __VA_ARGS__)(value)
