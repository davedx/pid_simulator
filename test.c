#include <stdlib.h>
#include <stdio.h>
#include "macros.h"
#include "types.h"

int ERROR = -1;

int add_positive (int a, int b) {
  if (c_assert(a >= 0) != true) {
    return ERROR;
  }
  if (c_assert(b >= 0) != true) {
    return ERROR;
  }
  return a + b;
}

// a kind of unit test suite for the assertion macros
int main (void) {
  // should not assert
  int c = add_positive(3, 4);
  if (c == ERROR) {
    printf("3,4 Returned ERROR\n");
  }

  // should assert
  int d = add_positive(-1, 2);
  if (d == ERROR) {
    printf("-1,2 Returned ERROR\n");
  }

  Vec2 ok_vec;
  ok_vec.x = 0;
  ok_vec.y = 0;
  c_assert_vec2(ok_vec, -1, 1);

  Vec2 out_of_range_vec;
  out_of_range_vec.x = -100.f;
  c_assert_vec2(out_of_range_vec, -1, 1);

  exit(0);
}
