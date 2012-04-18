// 
// staple.c
// Main entry point for the Staple language interpreter
//
// This file is part of Staple, the simple stack language interpreter.
// See the README file for more information, or the COPYING file for
// license info.
//

#include "staple.h"

int main(int argc, char** argv) {
  if (argc > 1) {
    if (strcmp(argv[1], "--version") == 0) {
      printf("Staple interpreter v%d.%d\n", MAJOR, MINOR);
      exit(EXIT_FAILURE);
    } else if (access(argv[1], R_OK) == 0) {
      // Execute the file
    } else {
      // There's something wrong with the file
      err(1, "%s", argv[1]);
    }
  } else {
    // Start the REPL
    wordexp_t exp_result;
    wordexp("~/.staple_hist", &exp_result, 0);
    linenoiseHistoryLoad(exp_result.we_wordv[0]);

    char* line;

    while((line = linenoise("staple> ")) != NULL) {
        if (line[0] != '\0') {
            printf(": %s\n", line);
            linenoiseHistoryAdd(line);
            linenoiseHistorySave(exp_result.we_wordv[0]); 
        }
        free(line);
    }

    wordfree(&exp_result);
  }

  return 0;
}
