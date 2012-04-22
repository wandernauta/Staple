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
  switch (val->t) {
    case STRING:
    case OP:
      free(val->d.s);
      break;
    case LIST:
      da_free(val->d.a);
      break;
    default:
      break;
  }
  free(val);
}

char* dv_describe(dvalue_t* val) {
  switch (val->t) {
    case INTEGER:
      return "Integer";
    case FLOAT:
      return "Float";
    case BOOL:
      return "Boolean";
    case STRING:
      return "String";
    case SYMBOL:
      return "Symbol";
    case OP:
      return "Op";
    case LIST:
      return "List";
    default:
      return "Unknown value";
  }
}

char* dv_fmt(dvalue_t* val) {
  char* out;
  int off = 0;

  switch (val->t) {
    case INTEGER:
      out = malloc(20);
      snprintf(out, 20, "%lld", val->d.i);
      return out;
    case FLOAT:
      out = malloc(20);
      snprintf(out, 20, "%f", val->d.f);
      return out;
    case BOOL:
      if (val->d.b) {
        return strdup("true");
      } else {
        return strdup("false");
      }
    case STRING:
      return strdup(val->d.s);
    case SYMBOL:
      out = malloc(20);
      out[0] = ':';
      strcpy(out + 1, symbol_decode(val->d.sym));
      return out;
    case OP:
      return strdup(val->d.s);
    case LIST:
      return da_fmt(val->d.a);
    default:
      return strdup("Unknown value");
  }
}

dvalue_t* dv_int(int64_t i) {
  dvalue_t* out = dv_init();
  out->t = INTEGER;
  out->d.i = i;
  return out;
}

dvalue_t* dv_float(double f) {
  dvalue_t* out = dv_init();
  out->t = FLOAT;
  out->d.f = f;
  return out;
}

dvalue_t* dv_bool(bool b) {
  dvalue_t* out = dv_init();
  out->t = BOOL;
  out->d.b = b;
  return out;
}

dvalue_t* dv_string(char* str) {
  dvalue_t* out = dv_init();
  out->t = STRING;
  out->d.s = strdup(str);
  return out;
}

dvalue_t* dv_symbol(char* sym) {
  dvalue_t* out = dv_init();
  out->t = SYMBOL;

  uint64_t s = symbol_encode(sym);
  if (!s) errx(1, "Invalid symbol %s", sym);
  else out->d.sym = s;

  return out;
}

dvalue_t* dv_op(char* op) {
  dvalue_t* out = dv_init();
  out->t = OP;
  out->d.s = strdup(op);
  return out;
}

dvalue_t* dv_list(void* a) {
  dvalue_t* out = dv_init();
  out->t = LIST;
  out->d.a = a;
  return out;
}
