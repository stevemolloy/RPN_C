#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "calc.h"

#define ASSERT(exp, msg) assert(exp && msg)
#define MAX_TOKENS 50

int main(void) {
  char calc_string[] = "10 2 + 4 7 / 22 - *";
  printf("Input string: \"%s\"\n", calc_string);

  char *token_list[MAX_TOKENS] = {0};
  int token_count = tokenize_string(calc_string, token_list);

  Stack s = {0};
  consume_tokens(&s, token_list, token_count);

  ASSERT(s.top == 1, "Stack not properly consumed");
  printf("Answer ==> %f\n", s.stack[--s.top]);

  return 0;
}

