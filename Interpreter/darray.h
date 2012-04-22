// 
// darray.h
// Header file for the dynamic array implementation
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "dvalue.h"

struct darray {
  dvalue_t** data;
  int size; // The amount of dvalue_t pointers in the array
  int cap;  // The amount of dvalue_t pointers it can store
  int pos;  // The position of the read head
};

typedef struct darray darray_t;

darray_t* da_init();
void da_push(darray_t* arr, dvalue_t* val);
void da_pop(darray_t* arr);
void da_swap(darray_t* arr);
dvalue_t* da_top(darray_t* arr);
dvalue_t* da_get(darray_t* arr, int i);
dvalue_t* da_next(darray_t* arr);
bool da_ensure(darray_t* arr, int minimum);
void da_free(darray_t* arr);
