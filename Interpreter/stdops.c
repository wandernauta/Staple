// 
// stdops.c
// Standard operation implementations for Staple
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "stdops.h"

// # Basic arithmetic

// + (add): Pop two numbers, push their sum
bool op_add(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_int(one->d.i + two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_float(one->d.f + two->d.f));
  } else {
    fprintf(stderr, "add: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// - (sub): Pop two numbers, push the difference
bool op_sub(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_int(one->d.i - two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_float(one->d.f - two->d.f));
  } else {
    fprintf(stderr, "sub: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// * (mul): Pop two numbers, push the product
bool op_mul(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_int(one->d.i * two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_float(one->d.f * two->d.f));
  } else {
    fprintf(stderr, "mul: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// / (div): Pop two numbers, push the division
bool op_div(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_int(one->d.i / two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_top(stk); da_pop(stk);
    dvalue_t* two = da_top(stk); da_pop(stk);
    da_push(stk, dv_float(one->d.f / two->d.f));
  } else {
    fprintf(stderr, "div: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// % (mod): Pop two numbers, push the remainder
bool op_mod(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  return true;
}

bool op_sum(darray_t* stk) {
  int sum = 0;
  while (stk->size > 0 && da_top(stk)->t == INTEGER) {
    sum += da_top(stk)->d.i;
    da_pop(stk);
  }

  da_push(stk, dv_int(sum));
  return true;
}

bool op_avg(darray_t* stk) {
  int sum = 0;
  int count = 0;
  while (stk->size > 0 && da_top(stk)->t == INTEGER) {
    sum += da_top(stk)->d.i;
    count += 1;
    da_pop(stk);
  }

  da_push(stk, dv_int(sum / count));
  return true;
}

// # List utilities

// cat: Concatenate two lists or strings
bool op_cat(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* one = da_top(stk); da_pop(stk);
  dvalue_t* two = da_top(stk); da_pop(stk);

  if (one->t == STRING && two->t == STRING) {
  } else {
    fprintf(stderr, "cat: expected (string, string) or (list, list)\n");
    return false;
  }

  dv_free(one); dv_free(two);
  return true;
}

// append: Pop an element, append it to the list below
bool op_append(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* elem = da_top(stk); da_pop(stk);
  dvalue_t* list = da_top(stk);
  return true;
}

// prepend: Pop an element, prepend it to the list below
bool op_prepend(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* elem = da_top(stk); da_pop(stk);
  dvalue_t* list = da_top(stk);
  return true;
}

// pack: Convert the whole stack to a list, then push that
bool op_pack(darray_t* stk) {
  if (stk->size == 0) {
    // Push an empty list
    da_push(stk, dv_list(da_init()));
  }
  return true;
}

// unpack: Pop a list from the stack, then push its contents
bool op_unpack(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  return true;
}

// head: Push a dupe of the first element of the list onto the stack
bool op_head(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);
  return true;
}

// tail: Push a dupe of the last element of the list onto the stack
bool op_tail(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);
  return true;
}

// count: Push the number of elements in the list onto the stack
bool op_count(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);

  return true;
}

// # Casting and conversion

// int: Convert an int, float, bool or string value to an integer
bool op_int(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);
  return true;
}

// float: Convert an int, float, or string value to a floating point value
bool op_float(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);

  int64_t intval;
  char* strptr;

  switch (top->t) {
    case INTEGER:
      intval = top->d.i;
      da_pop(stk);
      da_push(stk, dv_float((double)intval));
      break;
    case FLOAT:
      /* Nothing to do! */
      break;
    case STRING:
      strptr = top->d.s;
      da_pop(stk);
      da_push(stk, dv_float(strtod(strptr, NULL)));
      break;
    default:
      fprintf(stderr, "Unexpected %s (need int, float or string)\n", dv_describe(top));
      return false;
      break;
  }

  return true;
}

// bool: Convert anything to a bool
bool op_bool(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);
  return true;
}

// string: Convert anything to a string
bool op_string(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);
  return true;
}

// symbol: Convert a string to a symbol
bool op_symbol(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);

  if (top->t == STRING) {
    da_push(stk, dv_symbol(top->d.s));
    da_swap(stk);
    da_pop(stk);
    return true;
  } else {
    fprintf(stderr, "symbol: unexpected type\n");
    return false;
  }
}

// _ (negate): Negate the topmost number or boolean
bool op_negate(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);

  if (top->t == INTEGER) {
    top->d.i = -(top->d.i);
  } else if (top->t == FLOAT) {
    top->d.f = -(top->d.f);
  } else if (top->t == BOOL) {
    top->d.b = !(top->d.b);
  } else {
    fprintf(stderr, "negate: unexpected type\n");
    return false;
  }

  return true;
}

// # Logic

// both: Pop two bools, push whether they are both true (logical AND)
bool op_both(darray_t* stk) {
  if (da_ensure(stk, 2) && da_get(stk, 0)->t == BOOL && da_get(stk, 1)->t == BOOL) {
    bool one = da_top(stk)->d.b; da_pop(stk);
    bool two = da_top(stk)->d.b; da_pop(stk);
    
    da_push(stk, dv_bool(one && two));
    return true;
  } else {
    return false;
  }
}

// either: Pop two bools, push whether either of them are true (logical OR)
bool op_either(darray_t* stk) {
  if (da_ensure(stk, 2) && da_get(stk, 0)->t == BOOL && da_get(stk, 1)->t == BOOL) {
    bool one = da_top(stk)->d.b; da_pop(stk);
    bool two = da_top(stk)->d.b; da_pop(stk);
    
    da_push(stk, dv_bool(one || two));
    return true;
  } else {
    return false;
  }
}

// true: Push a true boolean value onto the stack
bool op_true(darray_t* stk) {
  da_push(stk, dv_bool(true));
  return true;
}

// false: Push a false boolean value onto the stack
bool op_false(darray_t* stk) {
  da_push(stk, dv_bool(false));
  return true;
}

// # Comparison

// eq: Push true if the top two elements are equal
bool op_eq(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  return true;
}

// gt: Push true if the top is greater than the second element
bool op_gt(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  return true;
}

// lt: Push true if the top is lesser than the second element
bool op_lt(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  return true;
}

// # Control structures

// do: Pop the top list, execute it
bool op_do(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t != LIST) { fprintf(stderr, "do: expected list\n"); return false; }

  darray_t* code = da_top(stk)->d.a; da_pop(stk);

  execute(code, stk, defs);

  return true;
}

// loop: Execute the top list indefinitely
bool op_loop(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t != LIST) { fprintf(stderr, "loop: expected list\n"); return false; }

  darray_t* code = da_top(stk)->d.a;
  while (1) { execute(code, stk, defs); }

  return true;
}

// times: Pop a list, execute it n times
bool op_times(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  op_swap(stk);

  dvalue_t* timesval = da_top(stk); da_pop(stk);
  if (timesval->t != INTEGER) { fprintf(stderr, "times: expected integer\n"); return false; }

  for (int i = 0; i < timesval->d.i; i++) {
    op_do(stk, defs);
  }
  return true;
}

// fi: Pop a list, execute it if the new top is true
bool op_fi(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  return true;
}

// # Stack management

// pop: Unconditionally pop the top of the stack
bool op_pop(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  da_pop(stk);
  return true;
}

// swap: Exchange the top of the stack with the second element
bool op_swap(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  da_swap(stk);
  return true;
}

// cycle: Cycle the bottom of the stack to the top
bool op_cycle(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (stk->size == 2) {
    op_swap(stk);
    return true;
  } else {
    return false;
  }
}

// dup: Duplicate the top of the stack
bool op_dup(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  return true;
}

// rev: Reverse the entire stack
bool op_rev(darray_t* stk) {
  return true;
}

// dump: Print the entire stack
bool op_dump(darray_t* stk) {
  for (int i = 0; i < stk->size; i++) {
    printf("%5d: %s (%s)\n", i, dv_fmt(da_get(stk, i)), dv_describe(da_get(stk, i)));
  }
  return true;
}

// depth: Push a count of the number of elements on the stack
bool op_depth(darray_t* stk) {
  da_push(stk, dv_int(stk->size));
  return true;
}

// # Input/output

// print: Output the string on top
bool op_print(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  printf("%s\n", dv_fmt(da_top(stk)));
  da_pop(stk);
  return true;
}

// println: Output the string on top, then a newline
bool op_println(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t == STRING) {
    puts(da_top(stk)->d.s);
  }
  return true;
}

// prompt: Ask the user for input, push it as a string
bool op_prompt(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  op_print(stk);
  char* buf = malloc(255);
  fgets(buf, 255, stdin);
  da_push(stk, dv_string(buf));
  return true;
}

// # Types and type handling

// type: Push the type of the top element as a number
bool op_type(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  da_push(stk, dv_int(da_top(stk)->t));
  return true;
}

// # Miscellany

// if: Do nothing (like nop)
bool op_if() {
  return true;
}

// nop: Do nothing (like if)
bool op_nop() {
  return true;
}

// exit: Exit immediately
bool op_exit() {
  exit(EXIT_SUCCESS);
  return true;
}
