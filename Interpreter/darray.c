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

dvalue_t* da_pop(darray_t* arr) {
  dvalue_t* top = da_top(arr);
  arr->size -= 1; 
  arr->data[arr->size] = NULL;
  return top;
}

void da_swap(darray_t* arr) {
  dvalue_t* b = da_pop(arr);
  dvalue_t* a = da_pop(arr);

  da_push(arr, b);
  da_push(arr, a);
}

void da_rev(darray_t* arr) {
  int end = arr->size - 1;
  for (int i = 0; i < (arr->size / 2); i++) {
    dvalue_t* t = arr->data[i];
    arr->data[i] = arr->data[end];
    arr->data[end] = t;

    end--;
  }
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

bool da_ensure(darray_t* arr, int minimum) {
  if (arr->size < minimum) {
    fprintf(stderr, "Expected stack depth of at least %d.\n", minimum);
    return false;
  } else {
    return true;
  }
}

char* da_fmt(darray_t* arr) {
  char* out = calloc(1, 1024);
  out[0] = '[';
  out[1] = ' ';
  int offs = 2;

  for (int i = 0; i < arr->size; i++) {
    char* fmt = dv_fmt(da_get(arr, i));
    strcpy(out + offs, fmt);
    offs += strlen(fmt);
    out[offs] = ' ';
    offs += 1;
  }

  out[offs] = ']';

  return out;
}

void da_free(darray_t* arr) {
  while (arr->size) da_pop(arr);
  free(arr);
}
