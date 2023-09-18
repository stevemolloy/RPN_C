#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "calc.h"

#define MAX_TOKENS 50

const char *prompt = "::> ";

int main(void) {
  Stack s = {0};
  VarList *v = new_varlist();

	initscr();			/* Start curses mode 		  */
  printw("Enter an RPN string for calculation\n");
  while (1) {
    clear();
    printw("Stack\n");
    for (int i=s.top-1; i>=0; i--) {
      switch (s.stack[i].type) {
        case TYPE_VAL:
          printw("%f\n", s.stack[i].val);
          break;
        case TYPE_NAME:
          printw("%s\n", s.stack[i].name);
          break;
      }
    }
    printw("\nVariables\n");
    for (int i=0; i<v->length; i++) {
      printw("%s ==> %f\n", v->defs[i].name, v->defs[i].value);
    }
    printw("\n%s ", prompt);
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

    consume_tokens(&s, v, token_list, token_count);
  }

	endwin();			/* End curses mode		  */

  return 0;
}

