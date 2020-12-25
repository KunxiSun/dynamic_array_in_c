#ifndef NBODY_H
#define NBODY_H

#include <unistd.h>

struct dynamic_array;

struct dynamic_array * dynamic_array_new(size_t initial_capacity);
void dynamic_array_add(struct dynamic_array *ary, void *value);
void * dynamic_array_get(struct dynamic_array *ary, size_t index);
void * dynamic_array_remove(struct dynamic_array *ary, size_t index);
void dynamic_array_destroy(struct dynamic_array * ary);

#endif