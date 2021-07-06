#include <stdio.h>

#define tst_debugging printf

#define true 1
#define false 0

#define c_assert(e) ((e) ? (true) : tst_debugging("%s, %d: assertion ’%s’ failed\n", __FILE__, __LINE__, #e), false)
