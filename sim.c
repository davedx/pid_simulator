#include <unistd.h>

#include "macros.h"
#include "renderer.h"
#include "controller.h"
#include "util.h"
#include "types.h"

struct SimState simState;

const float TARGET_UPDATE_FREQUENCY = 2.f;
const float MAX_VELOCITY = 2.f;

float timer = TARGET_UPDATE_FREQUENCY;
void update(float dt) {
  timer -= dt;

  if (timer < 0) {
    timer = TARGET_UPDATE_FREQUENCY;
    simState.target.x = (rand1() * 20.f) - 10.f;
    simState.target.y = (rand1() * 20.f) - 10.f;
    printf("Target at %.1f, %.1f\n", simState.target.x, simState.target.y);
  }
  vec2 accel = getAcceleration(&simState);
  simState.vehicle.acceleration.x = accel.x;
  simState.vehicle.acceleration.y = accel.y;

  simState.vehicle.velocity.x = simState.vehicle.velocity.x + simState.vehicle.acceleration.x * dt;
  simState.vehicle.velocity.y = simState.vehicle.velocity.y + simState.vehicle.acceleration.y * dt;

  simState.vehicle.position.x = simState.vehicle.position.x + simState.vehicle.velocity.x * dt;
  simState.vehicle.position.y = simState.vehicle.position.y + simState.vehicle.velocity.y * dt;
}

int main (int argc, char **argv) {
  seedRand();

  initRenderer(argc, argv, 1000, 600, update, &simState);
}

