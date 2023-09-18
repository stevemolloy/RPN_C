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

typedef struct VarDef {
  char* name;
  float value;
} VarDef;

typedef struct VarList {
  size_t length;
  size_t capacity;
  VarDef *defs;
} VarList;

VarList* new_varlist(void);
void free_varlist(VarList*);
int add_variable(VarList*, char*, float);
int find_variable(VarList*, char*, float*);
void consume_tokens(Stack*, VarList*, char*[], int);
void print_token_list(char*[]);
int tokenize_string(char[], char*[]);
void print_stack(Stack);
Token pop_from_stack(Stack*);
void push_to_stack(Stack*, Token);
Token float_to_token(float);
Token string_to_token(char*);
bool is_binary_op(char*);

#endif // !CALC_H
