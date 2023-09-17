#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <curses.h>

#include "calc.h"

#define DELIM " "

void consume_tokens(Stack *s, char *tok_list[], int tok_count) {
  float value = 0;
  for (int i=0; i<tok_count; i++) {
    if (is_binary_op(tok_list[i])) {
      if (s->top < 2) return;
      float b = pop_from_stack(s).val;
      float a = pop_from_stack(s).val;
      if (strcmp(tok_list[i], "+") == 0) {
        value = a + b;
      } else if (strcmp(tok_list[i], "-") == 0) {
        value = a - b;
      } else if (strcmp(tok_list[i], "*") == 0) {
        value = a * b;
      } else if (strcmp(tok_list[i], "/") == 0) {
        value = a / b;
      }
    } else {
      value = strtof(tok_list[i], NULL);
    }
    push_to_stack(s, float_to_token(value));
  }
}

Token float_to_token(float val) {
  Token tok = {
    .val = val,
    .name = "",
    .type = TYPE_VAL
  };
  return tok;
}

Token string_to_token(char name[]) {
  Token tok = {
    .val = 0,
    .name = name,
    .type = TYPE_VAL
  };
  return tok;
}

bool is_binary_op(char *tok) {
  if (strcmp(tok, "+") == 0) return true;
  if (strcmp(tok, "-") == 0) return true;
  if (strcmp(tok, "*") == 0) return true;
  if (strcmp(tok, "/") == 0) return true;
  return false;
}

void print_stack(Stack stack) {
  printf("Stack: ");
  for (int i=0; i<stack.top; i++) {
    printf("%f ", stack.stack[i].val);
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
  for(int i = 0; i < MAX_STACK_SIZE; i++) {
    if (str_array[i] == NULL) break;
    printf("%s ", str_array[i]);
  }
  printf("\n");
}

Token pop_from_stack(Stack *s) {
  assert(s->top>0 && "Attempt to pop from an empty stack.");
  return s->stack[--s->top];
}

void push_to_stack(Stack *s, Token t) {
  assert(s->top < MAX_STACK_SIZE && "Attempt to push to a full stack.");
  s->stack[s->top++] = t;
}

