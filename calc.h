#ifndef CALC_H
#define CALC_H

#define MAX_STACK_SIZE 50

typedef struct Stack {
  float stack[MAX_STACK_SIZE];
  size_t top;
} Stack;

void consume_tokens(Stack*, char*[], int);
void print_token_list(char*[]);
int tokenize_string(char[], char*[]);
void print_stack(Stack);
float pop_from_stack(Stack*);
void push_to_stack(Stack*, float);

#endif // !CALC_H
