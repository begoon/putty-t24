#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <inttypes.h>
#include "cmockery.h"

#include "t24.h"

void test_Bootstrap(void **state) {
  assert_int_equal(0LL, 0LL);
}

void modalfatalbox(char *fmt, ...) {}

void t24_basic_highlight(termchar *newline, int cols);

termline *newline(const char* chars) {
  int cols = strlen(chars);
  termline *line;
  int j;

  line = snew(termline);
  line->chars = snewn(cols, termchar);
  for (j = 0; j < cols; j++) {
    line->chars[j].chr = chars[j];
    line->chars[j].attr = '.';
  }

  return line;
}

void freeline(termline *line) {
  if (line) {
    sfree(line->chars);
    sfree(line);
  }
}

const char* decode_colors(const termchar* chars, int cols) {
  static const char codes[] = "01234567";
  static char buf[1024];
  int i;
  for (i = 0; i < cols; ++i) {
    int color = chars[i].attr;
    buf[i] = color == '.' ? color : codes[color & 0x07];
  }
  return buf;
}

const char* syntax(const char *chars) {
  size_t sz = strlen(chars);
  termline* line = newline(chars);
  t24_basic_highlight(line->chars, sz);
  const char* result = decode_colors(line->chars, sz);
  freeline(line);
  return result;
}

void test_Comments(void **state) {
  assert_string_equal(syntax("1234 !--------\n"), ".....3333333334");
}

int main(int argc, char* argv[]) {
  UnitTest tests[] = {
    unit_test(test_Bootstrap),
    unit_test(test_Comments),
  };
  return run_tests(tests);
}
