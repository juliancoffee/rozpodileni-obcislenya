#include "allocations.h"
#include <gtk/gtk.h>
#include <stdlib.h>

void *malloc_or_die(size_t size, char *reason) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    g_error("Allocation error when %s", reason);
  }
  return ptr;
}

void *calloc_or_die(size_t nmemb, size_t size, char *reason) {
  void *ptr = calloc(nmemb, size);
  if (ptr == NULL) {
    g_error("Allocation error when %s", reason);
  }
  return ptr;
}
void *realloc_or_die(void *ptr, size_t size, char *reason) {
  void *new_ptr = realloc(ptr, size);
  if (ptr == NULL) {
    g_error("Allocation error when %s", reason);
  }
  return new_ptr;
}
