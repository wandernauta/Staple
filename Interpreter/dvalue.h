//
// dvalue.h
// Header file for the Staple dynamic value implementation. 
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <stdint.h>
#include <stdlib.h>

enum type {
  INTEGER,
  FLOAT,
  STRING,
  SYMBOL,
  CALL,
  LIST
};

union data {
  int64_t i;    // Signed integer value
  double f;     // Floating-point value
  char* s;      // C-string pointer
  void* a;      // Dynamic array pointer 
  char sym[8];  // Symbol
  char op[8];   // Operator/method call
};

struct dvalue {
  enum type t;
  union data d;
};

typedef struct dvalue dvalue_t;

dvalue_t* dv_init();
void dv_free(dvalue_t* val);
