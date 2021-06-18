#include "stdlib.h"
#include "string.h"

#include "common.h"
#include "value.h"

int parse_expr(TValue* v, char* input, int i, char end);

int parse_num_expr(TValue* v, char* input, int i) {
  int initial = i;
  // Skip the opening parenthesis
  while (strchr("0123456789", input[i])) {
    i++;
  }

  // Account for null byte
  char* num = malloc(sizeof(char) * (i - initial) + 1);
  strncpy(num, input + i, i - initial);

  long actualNum = atol(num);
  v->num = actualNum;
  return i;
}

int parse_list_expr(TValue* v, char* input, int i) {
  // Skip the opening parenthesis
  i++;
  while (input[i] != ')') {
    TValue* val;
    parse_expr(val, input, i, '\0');
    val_push(v, val);
    i++;
  }

  return i;
}

int parse_sym_expr(TValue* v, char* input, int i) { char* part = calloc(1, 1); }

int parse_expr(TValue* v, char* input, int i, char end) {
  while (input[i] != end) {
    // Skip over whitespace
    if (strchr(" \t\r\n", input[i])) {
      i++;
      continue;
    }

    if (input[i] == '(') {
      TValue* list = val_list();
      val_push(v, list);
      i = parse_list_expr(list, input, i);
      continue;
    }

    i++;
  }

  return i;
}
