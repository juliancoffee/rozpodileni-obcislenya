#pragma once
#include <stddef.h>

void *malloc_or_die(size_t size, char *reason);
void *calloc_or_die(size_t nmemb, size_t size, char *reason);
void *realloc_or_die(void *ptr, size_t size, char *reason);
