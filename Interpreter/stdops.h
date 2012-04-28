// 
// stdops.h
// Definitions for the standard set of Staple operators ('words').
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "darray.h"
#include "dvalue.h"

bool execute(darray_t*, darray_t*, darray_t*);

bool op_add(darray_t* stk);
bool op_sub(darray_t* stk);
bool op_mul(darray_t* stk);
bool op_div(darray_t* stk);
bool op_mod(darray_t* stk);

bool op_sum(darray_t* stk);
bool op_avg(darray_t* stk);

bool op_cat(darray_t* stk);
bool op_append(darray_t* stk);
bool op_prepend(darray_t* stk);
bool op_pack(darray_t* stk);
bool op_unpack(darray_t* stk);
bool op_head(darray_t* stk);
bool op_tail(darray_t* stk);
bool op_count(darray_t* stk);

bool op_int(darray_t* stk);
bool op_float(darray_t* stk);
bool op_bool(darray_t* stk);
bool op_string(darray_t* stk);
bool op_symbol(darray_t* stk);
bool op_negate(darray_t* stk);

bool op_both(darray_t* stk);
bool op_either(darray_t* stk);
bool op_true(darray_t* stk);
bool op_false(darray_t* stk);

bool op_eq(darray_t* stk);
bool op_gt(darray_t* stk);
bool op_lt(darray_t* stk);

bool op_do(darray_t* stk, darray_t* defs);
bool op_loop(darray_t* stk, darray_t* defs);
bool op_times(darray_t* stk, darray_t* defs);
bool op_fi(darray_t* stk, darray_t* defs);

bool op_pop(darray_t* stk);
bool op_swap(darray_t* stk);
bool op_cycle(darray_t* stk);
bool op_dup(darray_t* stk);
bool op_rev(darray_t* stk);
bool op_dump(darray_t* stk);
bool op_depth(darray_t* stk);

bool op_print(darray_t* stk);
bool op_println(darray_t* stk);
bool op_prompt(darray_t* stk);

bool op_type(darray_t* stk);

bool op_def(darray_t* stk, darray_t* defs);
bool op_defs(darray_t* stk, darray_t* defs);
bool op_isdef(darray_t* stk, darray_t* defs);

bool op_if();
bool op_nop();
bool op_exit();
