// 
// darray.h
// Header file for the dynamic array implementation
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <stdlib.h>

#include "dvalue.h"

struct darray {
  dvalue_t** data;
  unsigned int size;
  unsigned int cap;
};

typedef struct darray darray_t;

darray_t* da_init();
void da_push(darray_t* arr, dvalue_t* val);
void da_pop(darray_t* arr);
dvalue_t* da_top(darray_t* arr);
dvalue_t* da_get(darray_t* arr, int i);
void da_free(darray_t* arr);
