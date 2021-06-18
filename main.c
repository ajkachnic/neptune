#include <stdio.h>
#include <stdlib.h>

#include <editline/history.h>
#include <editline/readline.h>

#include "common.h"
#include "parse.h"
// #include "value.h"

int main(int argc, char** argv) {
  puts("Welcome to neptune!");

  while (true) {
    char* input = readline("neptune> ");
    add_history(input);

    TValue* v = val_list();

    parse_expr(v, input, 0, '\0');

    val_println(v);

    free(input);
    free(v);
  }
}