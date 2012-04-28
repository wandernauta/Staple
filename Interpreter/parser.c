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
    if (equals(tok, "/*")) {
      // This starts a comment. Skip until closing comment marker.
      while (1) {
        tok = strtok(NULL, " \t\n");
        if (equals(tok, "*/")) break;
      }
    } else if (isnumeric(tok)) {
      // This is a number (integer or floating-point)
      if (strchr(tok, '.')) {
        da_push(out, dv_float(strtod(tok, NULL)));
      } else {
        da_push(out, dv_int(atoi(tok)));
      }
    } else if (startswith(tok, ':')) {
      // This is a symbol
      da_push(out, dv_symbol(tok + 1));
    } else if (equals(tok, "\"")) {
      // This starts a string. Collect it.
      char* str = calloc(1, 1024);
      int off = 0;
      while (1) {
        tok = strtok(NULL, " \t\n");
        if (equals(tok, "\"")) break;
        strcpy(str + off, tok);
        off += strlen(tok);
        str[off] = ' ';
        off += 1;
      }
      da_push(out, dv_string(str));
    } else if (equals(tok, "[")) {
      // This starts a list. Collect it.
      da_push(out, dv_list(parse(tok + 2, defs)));
    } else if (equals(tok, "]")) {
      // This ends a list. Return it.
      return out;
    } else {
      // This is a call
      da_push(out, dv_op(tok));
    }

    tok = strtok(NULL, " \t\n");
  }

  return out;
}
