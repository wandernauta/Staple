//
// darray.c
// Implementation for the Staple dynamic array (list/stack)
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "darray.h"

darray_t* da_init() {
  return calloc(1, sizeof(darray_t));
}

void da_push(darray_t* arr, dvalue_t* val) {
  if (arr->size < arr->cap) {
    arr->data[arr->size] = val;
  } else {
    arr->data = realloc(arr->data, ((arr->size * 2) + 1) * sizeof(darray_t));
    arr->data[arr->size] = val;
  }

  arr->size += 1;
}

void da_pop(darray_t* arr) {
  dv_free(arr->data[arr->size]);
  arr->size -= 1; 
}

dvalue_t* da_top(darray_t* arr) {
  return arr->data[arr->size];
}

dvalue_t* da_get(darray_t* arr, int i) {
  if (i >= 0) {
    return arr->data[i];
  } else {
    return arr->data[arr->size - (-i)];
  }
}

void da_free(darray_t* arr) {
  while (arr->size) da_pop(arr);
  free(arr);
}
