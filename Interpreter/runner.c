// 
// runner.c
// The function that executes a list of tokens
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "runner.h"

bool handle_op(dvalue_t* tok, darray_t* stack, darray_t* defs) {
  return true;
}

bool execute(darray_t* code, darray_t* stack, darray_t* defs) {
  for (int i = 0; i < code->size; i++) {
    dvalue_t* tok = code->data[i];

    switch (tok->t) {
      case SYMBOL:
      case INTEGER:
      case FLOAT:
        // This is a POD token, copy it onto the stack
        da_push(stack, tok);
        code->data[i] = NULL;
        break;
      case LIST:
        // This is a list token, copy it as well
        da_push(stack, tok);
        code->data[i] = NULL;
        break;
      case OP:
        handle_op(tok, stack, defs);
        break;
      default:
        errx(1, "Unexpected token type %s", dv_describe(tok));
        break;
    }
  }

  return true;
}
