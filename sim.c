#include <unistd.h>

#include "macros.h"
#include "cube.h"
#include "util.h"

struct Vec2 {
  float x;
  float y;
};

struct Vehicle {
  struct Vec2 position;
  struct Vec2 velocity;
  struct Vec2 acceleration;
};

int main (int argc, char **argv) {
  seedRand();
  initRenderer(argc, argv, 1000, 600);

  // printf("Sleeping...\n");
  // fflush(stdout);
  // sleep(2);

  // float r = rand1();
  // printf("hello %.5f\n", r);
  // fflush(stdout);
}

