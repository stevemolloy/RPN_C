#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "calc.h"

#define MAX_TOKENS 50
#define STACK_X_POS 40
#define VAR_X_POS 60

const char *prompt = "::> ";

int main(void) {
  Stack s = {0};
  VarList *v = new_varlist();

	initscr();			/* Start curses mode 		  */
  while (1) {
    clear();
    int y_pos = 0;
    move(0, STACK_X_POS);
    printw("Stack");
    for (int i=s.top-1; i>=0; i--) {
      move(++y_pos, STACK_X_POS);
      switch (s.stack[i].type) {
        case TYPE_VAL:
          printw("%f", s.stack[i].val);
          break;
        case TYPE_NAME:
          printw("%s", s.stack[i].name);
          break;
      }
    }
    y_pos = 0;
    move(y_pos, VAR_X_POS);
    printw("Variables");
    for (int i=0; i<v->length; i++) {
      move(++y_pos, VAR_X_POS);
      printw("%s ==> %f", v->defs[i].name, v->defs[i].value);
    }
    move(s.top > v->length ? s.top+2 : v->length+2, 0);
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

