// 
// parser.h
// A header file that goes with the Staple parser
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <stdbool.h>
#include <stdio.h> // TODO Remove this.
#include <string.h>

#include "darray.h"
#include "dvalue.h"

bool isnumeric(char* str);
bool startswith(char* str, char chr);
bool endswith(char* str, char chr);
bool equals(char* a, char* b);

darray_t* parse(char* code, darray_t* defs);
