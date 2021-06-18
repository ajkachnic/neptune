#include <stdio.h>
#include <stdlib.h>

#include <editline/history.h>
#include <editline/readline.h>

#include "common.h"

int main(int argc, char** argv) {
  puts("Welcome to neptune!");

  while (true) {
    char* input = readline("neptune> ");
    add_history(input);

    printf("You said: %s\n", input);

    free(input);
  }
}