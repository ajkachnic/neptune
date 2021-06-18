#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "value.h"

int parse_expr(TValue* v, char* input, int i, char end);

int parse_num_expr(TValue* v, char* input, int i) {
  v->tt = VAL_NUM;
  int initial = i;
  // Skip the opening parenthesis
  while (strchr("0123456789", input[i])) {
    i++;
  }

  // Account for null byte
  char* num = malloc(sizeof(char) * (i - initial) + 1);
  strncpy(num, input + i, i - initial);

  long actualNum = strtol(num, NULL, 10);
  v->num = actualNum;
  return i;
}

int parse_sym(TValue* v, char* input, int i) {
  char* part = calloc(1, 1);
  while (strchr("abcdefghijklmnopqrstuvwxyz"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789_+-*\\/=<>!&",
                input[i]) &&
         input[i] != '\0') {

    /* Append character to end of string */
    part = realloc(part, strlen(part) + 2);
    part[strlen(part) + 1] = '\0';
    part[strlen(part) + 0] = input[i];
    i++;
  }

  int is_num = strchr("-0123456789", part[0]);
  for (int i = 1; i < strlen(part); i++) {
    if (!strchr("0123456789", part[i])) {
      is_num = 0;
      break;
    }
  }

  /* Add Symbol or Number as lval */
  if (is_num) {
    errno = 0;
    long x = strtol(part, NULL, 10);
    val_push(v,
             errno != ERANGE ? val_num(x) : val_err("Invalid Number %s", part));
  } else {
    val_push(v, val_sym(part));
  }

  /* Free temp string */
  free(part);

  /* Return updated position in input */
  return i;
}

int parse_expr(TValue* v, char* input, int i, char end) {
  while (input[i] != end) {
    if (input[i] == '\0') {
      val_push(v, val_err("Missing %c at end of input", end));
      return strlen(input) + 1;
    }
    // Skip over whitespace
    if (strchr(" \t\r\n", input[i])) {
      i++;
      continue;
    }

    // Allow comments
    if (input[i] == ';') {
      while (input[i] != '\n' && input[i] != '\0')
        i++;
      i++;
      continue;
    }

    if (input[i] == '(') {
      TValue* list = val_list();
      val_push(v, list);
      i = parse_expr(list, input, i + 1, ')');
      continue;
    }

    if (strchr("abcdefghijklmnopqrstuvwxyz"
               "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "0123456789_+-*\\/=<>!&",
               input[i])) {
      i = parse_sym(v, input, i);
      continue;
    }

    val_push(v, val_err("Unknown Character %c", input[i]));
    return strlen(input) + 1;
  }

  return i + 1;
}
