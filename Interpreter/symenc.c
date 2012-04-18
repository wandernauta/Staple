//
// symenc.c
// Functions for encoding a symbol into 64 bits
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "symenc.h"

#define ASCII_A 97
#define ASCII_Z 122
#define SYMBITS 5
#define WIDTH 64
#define MAXCHARS (WIDTH / SYMBITS)

uint64_t symbol_encode(char* ascii) {
  int len = strlen(ascii);
  if (len == 0 || len > MAXCHARS) return 0;

  uint64_t out = 0;

  for (int i = 0; i < len; i++) {
    uint64_t chr = 0;

    // Lowercase the character
    ascii[i] = tolower(ascii[i]);

    // Treat some ASCII values specially
    if (ascii[i] == '\0') chr = 0;
    else if (ascii[i] == '_') chr = 1;
    else if (ascii[i] == '-') chr = 2;
    else if (ascii[i] == '!') chr = 3;
    else if (ascii[i] == '?') chr = 4;

    // Bring the rest of the alphabet into the 0-31 range
    else if (ascii[i] >= ASCII_A && ascii[i] <= ASCII_Z) {
      chr = (uint64_t)(ascii[i] - ASCII_A + 5);
    }

    // Whoa! Unknown char
    else {
      return 0;
    }

    // Shift the new character
    chr <<= i * SYMBITS;

    // Apply the shifted character to out
    out |= chr;
  }

  return out;
}

char* symbol_decode(uint64_t sym64) {
  char out[MAXCHARS] = "\0\0\0\0\0\0\0\0\0\0\0\0";

  for (int i = 0; i < MAXCHARS; i++) {
    // Mask the complete symbol with 0b11111 to get the lowest 5 bits
    uint64_t sym5 = sym64 & 0x1F;

    // Check if the string has ended (\0)
    if (sym5 == 0) break;

    // Reverse the encoding above
    if (sym5 == 1) out[i] = '_';
    else if (sym5 == 2) out[i] = '-';
    else if (sym5 == 3) out[i] = '!';
    else if (sym5 == 4) out[i] = '?';
    else *(out + i) = (char)(sym5 + ASCII_A - 5);

    // Shift SYMBITS places to get the next SYMBITS bits
    sym64 >>= SYMBITS;
  }

  return strdup(out);
}
