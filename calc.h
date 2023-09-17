#ifndef CALC_H
#define CALC_H

#define MAX_STACK_SIZE 1024

typedef enum TokenType {
  TYPE_VAL,
  TYPE_NAME
} TokenType;

typedef struct Token {
  float val;
  char* name;
  TokenType type;
} Token;

typedef struct Stack {
  Token stack[MAX_STACK_SIZE];
  size_t top;
} Stack;

void consume_tokens(Stack*, char*[], int);
void print_token_list(char*[]);
int tokenize_string(char[], char*[]);
void print_stack(Stack);
Token pop_from_stack(Stack*);
void push_to_stack(Stack*, Token);
Token float_to_token(float);
bool is_binary_op(char*);

#endif // !CALC_H
