#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#define DELIM " "
#define MAX_TOKENS 50
#define ASSERT_M(exp, msg) assert(((void)msg, exp))

typedef struct Stack {
  float stack[MAX_TOKENS];
  size_t top;
} Stack;

void print_token_list(char*[]);
int tokenize_string(char[], char*[]);
void print_stack(Stack);
float pop_from_stack(Stack*);
void push_to_stack(Stack*, float);

int main(void) {
  char calc_string[] = "10 2 + 4 7 / 22 - *";
  printf("Input string: \"%s\"\n", calc_string);

  char *token_list[MAX_TOKENS] = {0};
  int token_count = tokenize_string(calc_string, token_list);
  // printf("Token list: ");
  // print_token_list(token_list);

  Stack s = {0};
  for (int i=0; i<token_count; i++) {
    if (strcmp(token_list[i], "+") == 0) {
      float b = pop_from_stack(&s);
      float a = pop_from_stack(&s);
      push_to_stack(&s, a + b);
    }
    else if (strcmp(token_list[i], "-") == 0) {
      float b = pop_from_stack(&s);
      float a = pop_from_stack(&s);
      push_to_stack(&s, a - b);
    }
    else if (strcmp(token_list[i], "*") == 0) {
      float b = pop_from_stack(&s);
      float a = pop_from_stack(&s);
      push_to_stack(&s, a * b);
    }
    else if (strcmp(token_list[i], "/") == 0) {
      float b = pop_from_stack(&s);
      float a = pop_from_stack(&s);
      push_to_stack(&s, a / b);
    } else {
      s.stack[s.top++] = strtof(token_list[i], NULL);
    }
  }

  ASSERT_M(s.top == 1, "Stack not properly consumed");
  printf("Answer ==> %f\n", s.stack[--s.top]);

  return 0;
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

