#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "calc.h"

#define DELIM " "
#define MAX_TOKENS 50

void consume_tokens(Stack *s, char *tok_list[], int tok_count) {
  for (int i=0; i<tok_count; i++) {
    if (strcmp(tok_list[i], "+") == 0) {
      float b = pop_from_stack(s);
      float a = pop_from_stack(s);
      push_to_stack(s, a + b);
    }
    else if (strcmp(tok_list[i], "-") == 0) {
      float b = pop_from_stack(s);
      float a = pop_from_stack(s);
      push_to_stack(s, a - b);
    }
    else if (strcmp(tok_list[i], "*") == 0) {
      float b = pop_from_stack(s);
      float a = pop_from_stack(s);
      push_to_stack(s, a * b);
    }
    else if (strcmp(tok_list[i], "/") == 0) {
      float b = pop_from_stack(s);
      float a = pop_from_stack(s);
      push_to_stack(s, a / b);
    } else {
      s->stack[s->top++] = strtof(tok_list[i], NULL);
    }
  }
}

void print_stack(Stack stack) {
  printf("Stack: ");
  for (int i=0; i<stack.top; i++) {
    printf("%f ", stack.stack[i]);
  }
  printf("\n");
}

int tokenize_string(char input_string[], char *token_list[]) {
  char *tok = strtok(input_string, DELIM);
  if (tok == NULL) {
    printf("ERR: Input string is empty.");
    exit(1);
  }

  int token_counter = 0;
  do {
    // printf("Token %d: \"%s\"\n", token_counter, tok);
    token_list[token_counter++] = tok;
    tok = strtok(NULL, DELIM);
  } 
  while (tok != NULL);

  return token_counter;
}

void print_token_list(char* str_array[]) {
  for(int i = 0; i < MAX_TOKENS; i++) {
    if (str_array[i] == NULL) break;
    printf("%s ", str_array[i]);
  }
  printf("\n");
}

float pop_from_stack(Stack *s) {
  return s->stack[--s->top];
}

void push_to_stack(Stack *s, float f) {
  s->stack[s->top++] = f;
}

