// 
// runner.c
// The function that executes a list of tokens
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "runner.h"

bool handle_op(dvalue_t* tok, darray_t* stk, darray_t* d) {
  char* op = tok->d.s;
  if (false) {}

  // There must be a cleaner way to do this.

  else if (strcmp(op, "+") == 0)        { if(!op_add(stk))      return false; }
  else if (strcmp(op, "-") == 0)        { if(!op_sub(stk))      return false; }
  else if (strcmp(op, "*") == 0)        { if(!op_mul(stk))      return false; }
  else if (strcmp(op, "/") == 0)        { if(!op_div(stk))      return false; }
  else if (strcmp(op, "%") == 0)        { if(!op_mod(stk))      return false; }
  else if (strcmp(op, "sum") == 0)      { if(!op_sum(stk))      return false; }
  else if (strcmp(op, "avg") == 0)      { if(!op_avg(stk))      return false; }

  else if (strcmp(op, "cat") == 0)      { if(!op_cat(stk))      return false; }
  else if (strcmp(op, "append") == 0)   { if(!op_append(stk))   return false; }
  else if (strcmp(op, "prepend") == 0)  { if(!op_prepend(stk))  return false; }
  else if (strcmp(op, "pack") == 0)     { if(!op_pack(stk))     return false; }
  else if (strcmp(op, "unpack") == 0)   { if(!op_unpack(stk))   return false; }
  else if (strcmp(op, "head") == 0)     { if(!op_head(stk))     return false; }
  else if (strcmp(op, "tail") == 0)     { if(!op_tail(stk))     return false; }
  else if (strcmp(op, "count") == 0)    { if(!op_count(stk))    return false; }

  else if (strcmp(op, "int") == 0)      { if(!op_int(stk))      return false; }
  else if (strcmp(op, "float") == 0)    { if(!op_float(stk))    return false; }
  else if (strcmp(op, "bool") == 0)     { if(!op_bool(stk))     return false; }
  else if (strcmp(op, "string") == 0)   { if(!op_string(stk))   return false; }
  else if (strcmp(op, "symbol") == 0)   { if(!op_symbol(stk))   return false; }
  else if (strcmp(op, "negate") == 0)   { if(!op_negate(stk))   return false; }

  else if (strcmp(op, "both") == 0)     { if(!op_both(stk))     return false; }
  else if (strcmp(op, "either") == 0)   { if(!op_either(stk))   return false; }
  else if (strcmp(op, "true") == 0)     { if(!op_true(stk))     return false; }
  else if (strcmp(op, "false") == 0)    { if(!op_false(stk))    return false; }

  else if (strcmp(op, "eq") == 0)       { if(!op_eq(stk))       return false; }
  else if (strcmp(op, "gt") == 0)       { if(!op_gt(stk))       return false; }
  else if (strcmp(op, "lt") == 0)       { if(!op_lt(stk))       return false; }

  else if (strcmp(op, "do") == 0)       { if(!op_do(stk, d))    return false; }
  else if (strcmp(op, "loop") == 0)     { if(!op_loop(stk, d))  return false; }
  else if (strcmp(op, "times") == 0)    { if(!op_times(stk, d)) return false; }
  else if (strcmp(op, "fi") == 0)       { if(!op_fi(stk, d))    return false; }

  else if (strcmp(op, "pop") == 0)      { if(!op_pop(stk))      return false; }
  else if (strcmp(op, "swap") == 0)     { if(!op_swap(stk))     return false; }
  else if (strcmp(op, "cycle") == 0)    { if(!op_cycle(stk))    return false; }
  else if (strcmp(op, "dup") == 0)      { if(!op_dup(stk))      return false; }
  else if (strcmp(op, "rev") == 0)      { if(!op_rev(stk))      return false; }
  else if (strcmp(op, "dump") == 0)     { if(!op_dump(stk))     return false; }
  else if (strcmp(op, "depth") == 0)    { if(!op_depth(stk))    return false; }

  else if (strcmp(op, "print") == 0)    { if(!op_print(stk))    return false; }
  else if (strcmp(op, "println") == 0)  { if(!op_println(stk))  return false; }
  else if (strcmp(op, "prompt") == 0)   { if(!op_prompt(stk))   return false; }

  else if (strcmp(op, "type") == 0)     { if(!op_type(stk))     return false; }

  else if (strcmp(op, "if") == 0)       { if(!op_if())          return false; }
  else if (strcmp(op, "nop") == 0)      { if(!op_nop())         return false; }
  else if (strcmp(op, "exit") == 0)     { if(!op_exit())        return false; }

  else {
    fprintf(stderr, "Unknown operation %s\n", tok->d.s);
    return false;
  }

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
      case STRING:
        // This is a string token, copy it
        da_push(stack, tok);
        code->data[i] = NULL;
        break;
      case LIST:
        // This is a list token, copy it as well
        da_push(stack, tok);
        code->data[i] = NULL;
        break;
      case OP:
        if (!handle_op(tok, stack, defs)) return false; 
        break;
      default:
        errx(1, "Unexpected token type %s", dv_describe(tok));
        break;
    }
  }

  return true;
}
