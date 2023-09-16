#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DELIM " "
#define MAX_TOKENS 50

void print_token_list(char*[]);
void tokenize_string(char[], char*[]);

int main(void) {
  char *token_list[MAX_TOKENS] = {0};

  char calc_string[] = "1 2 + 3 *";
  printf("Input string: \"%s\"\n", calc_string);

  tokenize_string(calc_string, token_list);

  print_token_list(token_list);

  return 0;
}

void tokenize_string(char input_string[], char *token_list[]) {
  char *tok = strtok(input_string, DELIM);
  if (tok == NULL) {
    printf("ERR: Input string is empty.");
    exit(1);
  }

  int token_counter = 0;
  do {
    printf("Token %d: \"%s\"\n", token_counter, tok);
    token_list[token_counter++] = tok;
    tok = strtok(NULL, DELIM);
  } 
  while (tok != NULL);
}

void print_token_list(char* str_array[]) {
  for(int i = 0; i < MAX_TOKENS; i++) {
    if (str_array[i] == NULL) break;
    printf("%s ", str_array[i]);
  }
  printf("\n");
}

