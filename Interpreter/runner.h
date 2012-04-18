// 
// runner.h
// A header file that goes with the Staple runner
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <stdbool.h>

#include "darray.h"
#include "dvalue.h"
#include "stdops.h"

bool execute(darray_t* code, darray_t* stack, darray_t* defs);
