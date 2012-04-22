// 
// parser.c
// The function that parses a Staple program into an array of values
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "parser.h"

bool isnumeric(char* str) {
  char* p;
  strtod(str, &p);
  return (*p == '\0');
}

bool startswith(char* str, char chr) {
  return (str[0] == chr);
}

bool endswith(char* str, char chr) {
  return (str[strlen(str)] == chr);
}

bool equals(char* a, char* b) {
  return (strcmp(a, b) == 0);
}

darray_t* parse(char* code, darray_t* defs) {
  darray_t* out = da_init();

  char* tok = strtok(code, " \t\n");

  while (tok) {
    if (isnumeric(tok)) {
      // This is a number (integer or floating-point)
      da_push(out, dv_int(atoi(tok)));
    } else if (startswith(tok, ':')) {
      // This is a symbol
      da_push(out, dv_symbol(tok + 1));
    } else if (startswith(tok, '"')) {
      // This starts a string. Collect it.
      char* str = malloc(255);

      if (endswith(tok, '"')) {
        strncpy(str, tok + 1, strlen(tok) - 2);
        da_push(out, dv_string(str));
      } else {
      }
    } else if (equals(tok, "[")) {
      // This starts a list. Collect it.
      da_push(out, dv_list(parse(tok + 2, defs)));
    } else if (equals(tok, "]")) {
      // This ends a list. Return it.
      return out;
    } else if (equals(tok, "def")) {
      // This is a definition. Pop and store it.
    } else {
      // This is a call
      da_push(out, dv_op(tok));
    }

    tok = strtok(NULL, " \t\n");
  }

  return out;
}
