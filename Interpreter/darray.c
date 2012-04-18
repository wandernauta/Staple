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
  darray_t* arr = calloc(1, sizeof(darray_t*));
  arr->data = malloc(0);
  return arr;
}

void da_push(darray_t* arr, dvalue_t* val) {
  if (arr->size < arr->cap) {
    arr->data[arr->size] = val;
  } else {
    arr->cap  = ((arr->cap * 2) + 1);
    arr->data = realloc(arr->data, ((arr->cap) * sizeof(darray_t*)));
    
    // Fill the cap with null pointers
    for (dvalue_t** p = arr->data + arr->size; p < (arr->data + arr->cap); p++) {
      *p = NULL;
    }

    arr->data[arr->size] = val;
  }

  arr->size += 1;
}

void da_pop(darray_t* arr) {
  dv_free(arr->data[arr->size]);
  arr->size -= 1; 
}

dvalue_t* da_top(darray_t* arr) {
  return arr->data[arr->size - 1];
}

dvalue_t* da_get(darray_t* arr, int i) {
  if (i >= 0) {
    if (i <= arr->size) {
      return arr->data[i];
    } else {
      return NULL;
    }
  } else {
    return arr->data[arr->size - (-i)];
  }
}

dvalue_t* da_next(darray_t* arr) {
  dvalue_t* out = arr->data[arr->pos];
  arr->pos += 1;
  return out;
}

void da_free(darray_t* arr) {
  while (arr->size) da_pop(arr);
  free(arr);
}
