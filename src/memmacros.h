#pragma once
#include "allocations.h"
#include <assert.h>

/*
 * memory management: caller owns the data
 * allocate memory for one element on the heap of size `type`
 */
#define NEW(type, reason) malloc_or_die(sizeof(type), reason)

// trick to force semicolon on the callside
#define FORCE_SEMICOLON() static_assert(true, "")

/*
 * memory management: caller owns the data
 */
#define CREATE_BOXING_FOR(type, fn)                                            \
  type *fn(type value) {                                                       \
    type *boxed = NEW(type, "allocating " #type);                              \
    *boxed = value;                                                            \
    return boxed;                                                              \
  }                                                                            \
  FORCE_SEMICOLON()

#define DECLARE_BOXING_FOR(type, fn) type *fn(type value)

#define MATCH(T, target)                                                       \
  T:                                                                           \
  target

#define DISPATCH(value, ...) _Generic((value), __VA_ARGS__)(value)
