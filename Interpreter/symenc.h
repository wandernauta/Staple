// 
// symenc.h
// Compress ASCII text into a more condensed 64-bit number.
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

// The character set used for symbols is as follows:
// \0 a b c d e f g h i j k l m n o p q r s t u v w x y z _ -
// These 29 characters can be compressed into 5 bits each, which is what
// symbol_encode does.

#pragma once

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint64_t symbol_encode(char* ascii);
char* symbol_decode(uint64_t sym64);
