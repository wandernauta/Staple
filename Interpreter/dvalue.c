// 
// dvalue.c
// Functions that go with the Staple dynamic value system
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "dvalue.h"

dvalue_t* dv_init() {
  return calloc(1, sizeof(dvalue_t));
}

void dv_free(dvalue_t* val) {
  free(val);
}
