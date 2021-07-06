#include <unistd.h>

#include "macros.h"
#include "renderer.h"
#include "util.h"
#include "types.h"

struct SimState simState;

const float TARGET_UPDATE_FREQUENCY = 10.f;
float timer = TARGET_UPDATE_FREQUENCY;
void update(float dt) {
  timer -= dt;

  if (timer < 0) {
    timer = TARGET_UPDATE_FREQUENCY;
    simState.target.x = (rand1() * 100.f) - 50.f;
    simState.target.y = (rand1() * 100.f) - 50.f;
    printf("Target at %.1f, %.1f\n", simState.target.x, simState.target.y);
  }
}

int main (int argc, char **argv) {
  seedRand();

  initRenderer(argc, argv, 1000, 600, update, simState);
}

