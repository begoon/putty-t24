#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <inttypes.h>
#include "cmockery.h"

void test_Bootstrap(void **state) {
  assert_int_equal(0LL, 0LL);
}


int main(int argc, char* argv[]) {
  UnitTest tests[] = {
    unit_test(test_Bootstrap),
  };
  return run_tests(tests);
}
