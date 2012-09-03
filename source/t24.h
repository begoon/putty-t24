#ifndef PUTTY_T24_H
#define PUTTY_T24_H

#include "putty.h"
#include "terminal.h"

void t24_basic_highlight(termchar *newline, int cols, int jed_prefix_length);

int t24_is_jed_line(termchar *newline, int cols);
int t24_is_t24_line(termchar *newline, int cols);

extern int t24_highligh_on;
extern int t24_menu_mode;
extern int t24_jed_mode;

#endif

