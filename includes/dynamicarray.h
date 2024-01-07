#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// This macro define dynamic array structure with custom type.
// For example: if you pass int it will create DA_int data type
// and type of DA.items is intager.

#define CreateDynamicArray(type)                                               \
  typedef struct {                                                             \
    type *items;                                                               \
    size_t capacity;                                                           \
    size_t length;                                                             \
  } DA_##type;

#define CreateDynamicArrayFunctions(type)                                      \
  DA_##type da_##type##_create(size_t capacity) {                              \
    return (DA_##type){                                                        \
        .items = malloc(sizeof(type) * capacity),                              \
        .capacity = capacity,                                                  \
        .length = 0,                                                           \
    };                                                                         \
  }                                                                            \
                                                                               \
  size_t da_##type##_add(DA_##type *da, const type item) {                     \
    /* Resize items */                                                         \
    if (da->capacity < da->length + 1) {                                       \
      type *items = realloc(da->items, sizeof(type) * da->capacity * 2);       \
      if (items == NULL) {                                                     \
        perror("DYNAMIC ARRAY REALLOC ERROR!\n");                              \
      }                                                                        \
      da->items = items;                                                       \
    }                                                                          \
    /* Add item to items */                                                    \
    da->length++;                                                              \
    da->items[da->length] = item;                                              \
    return da->length;                                                         \
  }

#endif // DYNAMIC_ARRAY_h
