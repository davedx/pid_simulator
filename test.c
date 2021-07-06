#include <stdlib.h>

#define tst_debugging printf

#define true 1
#define false 0

#define c_assert(e) ((e) ? (true) : tst_debugging("%s, %d: assertion ’%s’ failed\n", __FILE__, __LINE__, #e), false)

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

int main (void) {
  // should not assert
  int c = add_positive(3, 4);
  if (c == ERROR) {
    printf("Returned ERROR, halting");
    exit(1);
  }

  // should assert
  int d = add_positive(-1, 2);
  if (d == ERROR) {
    printf("Returned ERROR, halting");
    exit(1);
  }

  exit(0);
}
