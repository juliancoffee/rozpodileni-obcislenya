#include <stddef.h>

int *element_at(int *matrix, size_t i, size_t j, size_t size) {
  return matrix + size * j + i;
}
