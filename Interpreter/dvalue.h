//
// dvalue.h
// Header file for the Staple dynamic value implementation. 
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "symenc.h"

// Forward declarations
struct darray;
void da_free(struct darray*);
char* da_fmt(struct darray* arr);
// End forward declarations

enum type {
  INTEGER,
  FLOAT,
  BOOL,
  STRING,
  SYMBOL,
  OP,
  LIST
};

union data {
  int64_t i;    // Signed integer value
  double f;     // Floating-point value
  bool b;       // Boolean value
  char* s;      // C-string pointer
  void* a;      // Dynamic array pointer 
  uint64_t sym; // Symbol
};

struct dvalue {
  enum type t;
  union data d;
};

typedef struct dvalue dvalue_t;

dvalue_t* dv_init();
void dv_free(dvalue_t* val);
char* dv_describe(dvalue_t* val);
char* dv_fmt(dvalue_t* val);

dvalue_t* dv_int(int64_t);
dvalue_t* dv_float(double);
dvalue_t* dv_bool(bool);
dvalue_t* dv_string(char*);
dvalue_t* dv_symbol(char*);
dvalue_t* dv_op(char*);
dvalue_t* dv_list(void*);
