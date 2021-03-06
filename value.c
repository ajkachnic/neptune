#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "value.h"

TValue* val_num(long x) {
  TValue* v = malloc(sizeof(TValue));
  v->tt = VAL_NUM;
  v->num = x;
  return v;
}

TValue* val_err(char* fmt, ...) {
  TValue* v = malloc(sizeof(TValue));
  v->tt = VAL_ERR;

  va_list va;
  va_start(va, fmt);

  v->err = malloc(512);

  vsnprintf(v->err, 511, fmt, va);

  v->err = realloc(v->err, strlen(v->err) + 1);

  va_end(va);

  return v;
}

TValue* val_sym(char* sym) {
  TValue* v = malloc(sizeof(TValue));
  v->tt = VAL_SYM;
  v->sym = malloc(strlen(sym) + 1);
  strcpy(v->sym, sym);
  return v;
}

TValue* val_list() {
  TValue* v = malloc(sizeof(TValue));
  v->tt = VAL_LIST;
  v->cell = NULL;
  v->count = 0;
  return v;
}

// Free all of the memory used by a Value
// Can I get a hurray for manual memory management?
// ...
// No? Alright then
void val_del(TValue* v) {
  switch (v->tt) {
  case VAL_NUM:
    break;
  case VAL_ERR:
    free(v);
    break;
  case VAL_SYM:
    free(v->sym);
    break;
  case VAL_LIST:
    for (int i = 0; i < v->count; i++) {
      // Free individual elements
      val_del(v->cell[i]);
    }
    // Free the space used to store pointers
    free(v->cell);
  }
}

void val_push(TValue* root, TValue* push) {
  root->count += 1;
  // Expand the internal cell
  root->cell = realloc(root->cell, sizeof(TValue*) * root->count);
  root->cell[root->count - 1] = push;
}

void val_print(TValue* v);

void val_expr_print(TValue* v, char open, char close) {
  putchar(open);
  for (int i = 0; i < v->count; i++) {

    /* Print Value contained within */
    val_print(v->cell[i]);

    /* Don't print trailing space if last element */
    if (i != (v->count - 1)) {
      putchar(' ');
    }
  }
  putchar(close);
}

void val_print(TValue* v) {
  switch (v->tt) {
  case VAL_NUM:
    printf("%li", v->num);
    break;
  case VAL_ERR:
    printf("Error: %s", v->err);
    break;
  case VAL_SYM:
    printf("%s", v->sym);
    break;
  case VAL_LIST:
    val_expr_print(v, '(', ')');
    break;
  }
}
void val_println(TValue* v) {
  val_print(v);
  putchar('\n');
}
