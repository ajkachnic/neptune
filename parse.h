#include "common.h"
#include "value.h"

int parse_expr(TValue* v, char* input, int i, char end);

int parse_num_expr(TValue* v, char* input, int i); 

int parse_list_expr(TValue* v, char* input, int i);

// int parse_sym_expr(TValue* v, char* input, int i); 

int parse_expr(TValue* v, char* input, int i, char end);