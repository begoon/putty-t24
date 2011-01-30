#ifndef PUTTY_T24_H
#define PUTTY_T24_H

#include "putty.h"
#include "terminal.h"

void t24_basic_highlight(termchar *newline, int cols);
extern int t24_highligh_on;
extern int t24_menu_mode;
extern int t24_jed_mode;

#endif

