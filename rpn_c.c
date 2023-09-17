#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <curses.h>

#include "calc.h"

#define ASSERT(exp, msg) assert(exp && msg)
#define MAX_TOKENS 50

const char *prompt = "::> ";

int main(void) {
  Stack s = {0};
  // char calc_string[] = "10 2 + 4 7 / 22 - *";

	initscr();			/* Start curses mode 		  */
  printw("Enter an RPN string for calculation\n");
  while (1) {
    printw("%s ", prompt);
    refresh();

    char calc_string[MAX_TOKENS];
    if (getnstr(calc_string, MAX_TOKENS)) {
      printw("Could not read string. Terminating.");
      exit(1);
    }

    if (strcmp(calc_string, "quit") == 0 || strcmp(calc_string, "exit") == 0) {
      break;
    }

    char *token_list[MAX_TOKENS] = {0};
    int token_count = tokenize_string(calc_string, token_list);

    consume_tokens(&s, token_list, token_count);

    ASSERT(s.top == 1, "Stack not properly consumed");
    printw("Answer ==> %f\n", s.stack[--s.top]);
  }

	endwin();			/* End curses mode		  */

  return 0;
}

