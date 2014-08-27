//   
// stdops.c  
// Standard operation implementations for Staple  
//  
// This file is part of Staple, the simple stack language interpreter.  
// See the README file for more information, or the COPYING file for  
// license info.  
//  

#include "stdops.h"

//  
// ## Basic arithmetic
//  

// add (`+`): Pop two numbers, push their sum  
bool op_add(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_pop(stk);
    dvalue_t* two = da_pop(stk);
    da_push(stk, dv_int(one->d.i + two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_pop(stk);
    dvalue_t* two = da_pop(stk);
    da_push(stk, dv_float(one->d.f + two->d.f));
  } else {
    fprintf(stderr, "add: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// sub (`-`): Pop two numbers, push the difference  
bool op_sub(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* two = da_pop(stk);
    dvalue_t* one = da_pop(stk);
    da_push(stk, dv_int(one->d.i - two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* two = da_pop(stk);
    dvalue_t* one = da_pop(stk);
    da_push(stk, dv_float(one->d.f - two->d.f));
  } else {
    fprintf(stderr, "sub: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// mul (`*`): Pop two numbers, push the product  
bool op_mul(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* one = da_pop(stk);
    dvalue_t* two = da_pop(stk);
    da_push(stk, dv_int(one->d.i * two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* one = da_pop(stk);
    dvalue_t* two = da_pop(stk);
    da_push(stk, dv_float(one->d.f * two->d.f));
  } else {
    fprintf(stderr, "mul: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// div (`/`): Pop two numbers, push the division  
bool op_div(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == INTEGER && da_get(stk, -2)->t == INTEGER) {
    dvalue_t* two = da_pop(stk);
    dvalue_t* one = da_pop(stk);
    da_push(stk, dv_int(one->d.i / two->d.i));
  } else if (da_get(stk, -1)->t == FLOAT && da_get(stk, -2)->t == FLOAT) {
    dvalue_t* two = da_pop(stk);
    dvalue_t* one = da_pop(stk);
    da_push(stk, dv_float(one->d.f / two->d.f));
  } else {
    fprintf(stderr, "div: expected (int, int) or (float, float)\n");
    return false;
  }

  return true;
}

// mod (`%`): Pop two numbers, push the remainder  
bool op_mod(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  return true;
}

// sum: Pop while the top is a number, then push the sum  
bool op_sum(darray_t* stk) {
  int sum = 0;
  while (stk->size > 0 && da_top(stk)->t == INTEGER) {
    dvalue_t* top = da_pop(stk);
    sum += top->d.i;
  }

  da_push(stk, dv_int(sum));
  return true;
}

// avg: Pop while the top is a number, then push the average  
bool op_avg(darray_t* stk) {
  int sum = 0;
  int count = 0;
  while (stk->size > 0 && da_top(stk)->t == INTEGER) {
    dvalue_t* top = da_pop(stk);
    sum += top->d.i;
    count += 1;
  }

  da_push(stk, dv_int(sum / count));
  return true;
}

//
// ## More advanced maths
//

// ceil: Pop a float, then round it up  
bool op_ceil(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "ceil: expected float\n"); return false; }
  da_push(stk, dv_float(ceil(da_pop(stk)->d.f)));
  return true;
}

// floor: Pop a float, then round it down  
bool op_floor(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "floor: expected float\n"); return false; }
  da_push(stk, dv_float(floor(da_pop(stk)->d.f)));
  return true;
}

// trunc: Pop a float, then truncate it (round toward zero)  
bool op_trunc(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "trunc: expected float\n"); return false; }
  da_push(stk, dv_float(trunc(da_pop(stk)->d.f)));
  return true;
}

// abs: Pop an integer, push its absolute value  
bool op_abs(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != INTEGER) { fprintf(stderr, "abs: expected integer\n"); return false; }
  da_push(stk, dv_int(abs(da_pop(stk)->d.i)));
  return true;
}

// exp: Pop a float x, calculate e^x, push the result  
bool op_exp(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "exp: expected float\n"); return false; }
  da_push(stk, dv_float(exp(da_pop(stk)->d.f)));
  return true;
}

// pi: Push pi (about 3.14)  
bool op_pi(darray_t* stk) {
  da_push(stk, dv_float(3.14159265359));
  return true;
}

// sin: Pop a float, calculate its sine (radians)  
bool op_sin(darray_t* stk) {
  da_ensure(stk, 1);
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "sin: expected float\n"); return false; }
  da_push(stk, dv_float(sin(da_pop(stk)->d.f)));
  return true;
}

// sin: Pop a float, calculate its cosine (radians)  
bool op_cos(darray_t* stk) {
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "cos: expected float\n"); return false; }
  da_push(stk, dv_float(cos(da_pop(stk)->d.f)));
  return true;
}

// sin: Pop a float, calculate its tangent (radians)  
bool op_tan(darray_t* stk) {
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "tan: expected float\n"); return false; }
  da_push(stk, dv_float(tan(da_pop(stk)->d.f)));
  return true;
}

// log: Pop a float, push its natural logarithm  
bool op_log(darray_t* stk) {
  if (da_top(stk)->t != FLOAT) { fprintf(stderr, "log: expected float\n"); return false; }
  da_push(stk, dv_float(log(da_pop(stk)->d.f)));
  return true;
}

// pow: Pop two floats a and b, push a^b  
bool op_pow(darray_t* stk) {
  if (da_top(stk)->t != FLOAT || da_get(stk, -2)->t != FLOAT) { fprintf(stderr, "pow: expected (float, float)\n"); return false; }
  dvalue_t* y = da_pop(stk);
  dvalue_t* x = da_pop(stk);

  da_push(stk, dv_float(pow(x->d.f, y->d.f)));

  return true;
}

// hypot: Pop two floats a and b, push sqrt(x*x+y*y)  
bool op_hypot(darray_t* stk) {
  if (da_top(stk)->t != FLOAT || da_get(stk, -2)->t != FLOAT) { fprintf(stderr, "hypot: expected (float, float)\n"); return false; }
  dvalue_t* y = da_pop(stk);
  dvalue_t* x = da_pop(stk);

  da_push(stk, dv_float(hypot(x->d.f, y->d.f)));

  return true;
}

//  
// ## List utilities
//  

// cat: Concatenate two lists or strings  
bool op_cat(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* two = da_pop(stk);
  dvalue_t* one = da_pop(stk);

  if (one->t == STRING && two->t == STRING) {
    int len = strlen(one->d.s) + strlen(two->d.s);
    char* dest = malloc(len);
    strcpy(dest, one->d.s);
    strcat(dest, two->d.s);
    da_push(stk, dv_string(dest));
  } else if (one->t == LIST && two->t == LIST) {
    darray_t* l1 = (darray_t*)one->d.a;
    darray_t* l2 = (darray_t*)two->d.a;

    for (int i = 0; i < l2->size; i++) {
      da_push(l1, da_get(l2, i));
    }

    da_push(stk, one);
  } else {
    fprintf(stderr, "cat: expected (string, string) or (list, list)\n");
    return false;
  }

  return true;
}

// append: Pop an element, append it to the list below  
bool op_append(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* elem = da_pop(stk);
  dvalue_t* list = da_top(stk);
  da_push(list->d.a, elem);
  return true;
}

// prepend: Pop an element, prepend it to the list below  
bool op_prepend(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;
  dvalue_t* elem = da_pop(stk);

  /* Make a new list */
  darray_t* new = da_init();

  /* Add the popped element to the list */
  da_push(new, elem);

  /* Push the new list onto the stack */
  da_push(stk, dv_list(new));

  /* Swap the stack top */
  da_swap(stk);

  /* Concatenate the top two lists */
  op_cat(stk);

  return true;
}

// pack: Convert the whole stack to a list, then push that  
bool op_pack(darray_t* stk) {
  darray_t* list = da_init();
  dvalue_t* val = NULL;

  for (int i = 0; i < stk->size; i++) {
    val = da_get(stk, i);
    da_push(list, val);
  }

  da_push(stk, dv_list(list));
  return true;
}

// unpack: Pop a list from the stack, then push its contents  
bool op_unpack(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;

  dvalue_t* listval = da_pop(stk);
  darray_t* list = listval->d.a;

  for (int i = 0; i < list->size; i++) {
    da_push(stk, da_get(list, i));
  }

  return true;
}

// head: Push a dupe of the first element of the list onto the stack  
bool op_head(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);

  da_push(stk, da_get(list->d.a, 0));
  return true;
}

// tail: Push a dupe of the last element of the list onto the stack  
bool op_tail(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);

  da_push(stk, da_top(list->d.a));
  return true;
}

// count: Push the number of elements in the list onto the stack  
bool op_count(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* list = da_top(stk);

  da_push(stk, dv_int(((darray_t*)list->d.a)->size));
  return true;
}

//  
// ## Casting and conversion
//  

// int: Convert an int, float, bool or string value to an integer  
bool op_int(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);

  double fval;
  char* str;

  switch (top->t) {
    case INTEGER:
      /* Nothing to do! */
      break;
    case FLOAT:
      fval = top->d.f;
      da_pop(stk);
      da_push(stk, dv_int((int)fval));
      break;
    case STRING:
      str = top->d.s;
      da_pop(stk);
      da_push(stk, dv_int(atoi(str)));
      break;
    case BOOL:
      if (top->d.b == true) {
        da_pop(stk);
        da_push(stk, dv_int(1));
      } else {
        da_pop(stk);
        da_push(stk, dv_int(0));
      }
      break;
    default:
      fprintf(stderr, "Unexpected %s (need int, float, string or bool)\n", dv_describe(top));
      return false;
      break;
  }

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

// bool: Convert an integer to a bool  
bool op_bool(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_top(stk);

  switch (top->t) {
    case INTEGER:
      if (top->d.i == 0) {
        da_push(stk, dv_bool(false));
      } else {
        da_push(stk, dv_bool(true));
      }
      break;
    default:
      fprintf(stderr, "bool: Unexpected %s (need int)\n", dv_describe(top));
      return false;
      break;
  }

  return true;
}

// string: Convert anything to a string  
bool op_string(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  dvalue_t* top = da_pop(stk);
  da_push(stk, dv_string(dv_fmt(top)));
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
    fprintf(stderr, "symbol: Unexpected %s (need string)\n", dv_describe(top));
    return false;
  }
}

// negate: Negate the topmost number or boolean  
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
    fprintf(stderr, "negate: Unexpected %s (need integer, float or bool)\n", dv_describe(top));
    return false;
  }

  return true;
}

// chr: Convert the topmost integer to a single-character string
bool op_chr(darray_t* stk) {
  if (!da_ensure(stk, 1) || da_top(stk)->t != INTEGER) return false;

  dvalue_t* integer = da_pop(stk);
  int64_t intval = integer->d.i;
  char* str = calloc(1, 2);
  str[0] = (char)intval;
  da_push(stk, dv_string(str));

  return true;
}

// ord: Convert a single-character string to an integer
bool op_ord(darray_t* stk) {
  if (!da_ensure(stk, 1) || da_top(stk)->t != STRING) return false;

  dvalue_t* string = da_pop(stk);
  char* strval = string->d.s;
  da_push(stk, dv_int((int)strval[0]));

  return true;
}

//  
// ## Logic
//  

// both: Pop two bools, push whether they are both true (logical AND)  
bool op_both(darray_t* stk) {
  if (da_ensure(stk, 2) && da_get(stk, -1)->t == BOOL && da_get(stk, -2)->t == BOOL) {
    bool one = da_pop(stk)->d.b;
    bool two = da_pop(stk)->d.b;
    
    da_push(stk, dv_bool(one && two));
    return true;
  } else {
    return false;
  }
}

// either: Pop two bools, push whether either of them are true (logical OR)  
bool op_either(darray_t* stk) {
  if (da_ensure(stk, 2) && da_get(stk, -1)->t == BOOL && da_get(stk, -2)->t == BOOL) {
    bool one = da_pop(stk)->d.b;
    bool two = da_pop(stk)->d.b;
    
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

//  
// ## Comparison
//  

// eq: Pop two elements, then push true if they are equal  
bool op_eq(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  dvalue_t* two = da_pop(stk);
  dvalue_t* one = da_pop(stk);

  da_push(stk, dv_bool((memcmp(one, two, sizeof(dvalue_t)) == 0)));

  return true;
}

// gt: Pop two elements, then push true if the second is greater than the first  
bool op_gt(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  dvalue_t* two = da_pop(stk);
  dvalue_t* one = da_pop(stk);

  if (one->t == INTEGER && two->t == INTEGER) {
    if (one->d.i > two->d.i) da_push(stk, dv_bool(true));
    else da_push(stk, dv_bool(false));
    return true;
  } if (one->t == FLOAT && two->t == FLOAT) {
    if (one->d.f > two->d.f) da_push(stk, dv_bool(true));
    else da_push(stk, dv_bool(false));
    return true;
  } else {
    return false;
  }
}

// lt: Pop two elements, then push true if the second is lesser than the first  
bool op_lt(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  dvalue_t* two = da_pop(stk);
  dvalue_t* one = da_pop(stk);

  if (one->t == INTEGER && two->t == INTEGER) {
    if (one->d.i < two->d.i) da_push(stk, dv_bool(true));
    else da_push(stk, dv_bool(false));
    return true;
  } if (one->t == FLOAT && two->t == FLOAT) {
    if (one->d.f < two->d.f) da_push(stk, dv_bool(true));
    else da_push(stk, dv_bool(false));
    return true;
  } else {
    return false;
  }
  return true;
}

//  
// ## Control structures
//  

// do: Pop the top list, execute it  
bool op_do(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t != LIST) { fprintf(stderr, "do: expected list\n"); return false; }

  darray_t* code = da_top(stk)->d.a; da_pop(stk);

  execute(code, stk, defs);

  return true;
}

// loop: Pop the top list, execute it indefinitely  
bool op_loop(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t != LIST) { fprintf(stderr, "loop: expected list\n"); return false; }

  darray_t* code = da_pop(stk)->d.a;
  while (1) { execute(code, stk, defs); }

  return true;
}

// times: Pop a list, execute it n times  
bool op_times(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 2)) return false;
  if (!(da_get(stk, -2)->t == LIST && da_get(stk, -1)->t == INTEGER)) {
    fprintf(stderr, "times: expected (list, integer)\n");
    return false;
  } 

  int count = da_top(stk)->d.i; da_pop(stk);
  darray_t* code = da_top(stk)->d.a; da_pop(stk);

  for (int i = 0; i < count; i++) {
    execute(code, stk, defs);
  }

  return true;
}

// fi: Pop a list, execute it if the new top is true  
bool op_fi(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 2)) return false;
  if (!(da_get(stk, -1)->t == LIST && da_get(stk, -2)->t == BOOL)) {
    fprintf(stderr, "fi: expected (boolean, list)\n");
    return false;
  } 

  darray_t* code = da_top(stk)->d.a; da_pop(stk);
  bool cond = da_top(stk)->d.b; da_pop(stk);

  if (cond) {
    execute(code, stk, defs);
  }

  return true;
}

// call: Pop a symbol, execute it  
bool op_call(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (da_top(stk)->t != SYMBOL) { fprintf(stderr, "call: expected symbol\n"); return false; }

  dvalue_t* sym = da_pop(stk);

  for (int i = 0; i < defs->size; i += 2) {
    if (da_get(defs, i)->d.sym == sym->d.sym) {
      execute((darray_t*)da_get(defs, i+1)->d.a, stk, defs);
      return true;
    }
  }

  fprintf(stderr, "call: unknown operation %s\n", symbol_decode(sym->d.sym));
  return false;
}

//  
// ## Stack management
//  

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

  dvalue_t* new = malloc(sizeof(dvalue_t));
  memcpy(new, da_top(stk), sizeof(dvalue_t));
  da_push(stk, new);

  return true;
}

// over: Duplicate the item below the top  
bool op_over(darray_t* stk) {
  if (!da_ensure(stk, 2)) return false;

  dvalue_t* new = malloc(sizeof(dvalue_t));
  memcpy(new, da_get(stk, -2), sizeof(dvalue_t));
  da_push(stk, new);

  return true;
}

// rev: Reverse the entire stack  
bool op_rev(darray_t* stk) {
  da_rev(stk);
  return true;
}

// dump: Print the entire stack  
bool op_dump(darray_t* stk) {
  for (int i = 0; i < stk->size; i++) {
    char* fmt = dv_fmt(da_get(stk, i));
    char* desc = dv_describe(da_get(stk, i));
    printf("%5d: %s (%s)\n", i, fmt, desc);
  }
  return true;
}

// depth: Push a count of the number of elements on the stack  
bool op_depth(darray_t* stk) {
  da_push(stk, dv_int(stk->size));
  return true;
}

//  
// ## Input/output
//  

// print: Output the string on top  
bool op_print(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  char* fmt = dv_fmt(da_pop(stk));
  printf("%s", fmt);
  return true;
}

// println: Output the string on top, then a newline  
bool op_println(darray_t* stk) {
  if (!op_print(stk)) return false;
  puts("");
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

//  
// ## Types and type handling
//  

// type: Push the type of the top element as a number  
bool op_type(darray_t* stk) {
  if (!da_ensure(stk, 1)) return false;
  da_push(stk, dv_int(da_top(stk)->t));
  return true;
}

//
// ## Definition management
//

// def: Define a function  
bool op_def(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 2)) return false;

  if (da_get(stk, -1)->t == LIST && da_get(stk, -2)->t == SYMBOL) {
    dvalue_t* fun = da_pop(stk);
    dvalue_t* sym = da_pop(stk);

    da_push(defs, sym);
    da_push(defs, fun);

    return true;
  } else {
    fprintf(stderr, "def: expected (symbol, list)\n");
    return false;
  }
}

// defs: Push a list of defined functions to the stack as symbols  
bool op_defs(darray_t* stk, darray_t* defs) {
  for (int i = 0; i < (defs->size/2); i++) {
    da_push(stk, da_get(defs, i*2));
  }

  return true;
}

// isdef: Push whether a symbol is defined as a function or not  
bool op_isdef(darray_t* stk, darray_t* defs) {
  for (int i = 0; i < (defs->size/2); i++) {
    if (da_top(stk)->d.sym == da_get(defs, i)->d.sym) {
      da_pop(stk);
      da_push(stk, dv_bool(true));
      return true;
    }
  }

  da_push(stk, dv_bool(false));
  return true;
}

//  
// ## Miscellany
//  

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

// assert: Pop a list, execute it, then print an error message if it doesn't return true
bool op_assert(darray_t* stk, darray_t* defs) {
  if (!da_ensure(stk, 1)) return false;
  if (!(da_get(stk, -1)->t == LIST)) {
    fprintf(stderr, "assert: expected list to execute\n");
    return false;
  }

  op_dup(stk);
  op_string(stk);
  op_swap(stk);
  op_do(stk, defs);

  if (!da_ensure(stk, 1)) return false;
  if (!(da_get(stk, -1)->t == BOOL)) {
    fprintf(stderr, "assert: expected result to be boolean\n");
    return false;
  }

  bool cond = da_top(stk)->d.b; da_pop(stk);

  if (!cond) {
    fprintf(stderr, "assert: assertion failed: %s\n", da_pop(stk)->d.s);
    exit(EXIT_FAILURE);
  } else {
    da_pop(stk); /* Pop the string description of the function */
  }

  return true;
}
