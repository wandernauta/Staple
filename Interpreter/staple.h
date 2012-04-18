// 
// staple.h
// Header file for the entry point of the Staple interpreter
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#pragma once

#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wordexp.h>

#include "parser.h"
#include "runner.h"
#include "vendor/linenoise.h"

#define MAJOR 0
#define MINOR 1

int main(int argc, char** argv);
