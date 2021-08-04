#include <unistd.h>

#include "macros.h"
#include "renderer.h"
#include "controller.h"
#include "util.h"
#include "types.h"

SimState simState;

const float TARGET_UPDATE_FREQUENCY = 20.f;
const float LOG_FREQUENCY = 1.f;
const float MAX_VELOCITY = 2.f;

float timer = 0;
float logTimer = LOG_FREQUENCY;

void update(float dt) {
  timer -= dt;
  logTimer -= dt;

  if (logTimer < 0) {
    logTimer = LOG_FREQUENCY;
    printf("Vehicle accel %.2f,%.2f vel %.2f,%.2f pos %.2f,%.2f\n",
      simState.vehicle.acceleration.x, simState.vehicle.acceleration.y,
      simState.vehicle.velocity.x, simState.vehicle.velocity.y,
      simState.vehicle.position.x, simState.vehicle.position.y);
  }

  if (timer < 0) {
    timer = TARGET_UPDATE_FREQUENCY;
    simState.target.x = (rand1() * 60.f) - 30.f;
    simState.target.y = (rand1() * 60.f) - 30.f;
    printf("Target at %.1f, %.1f\n", simState.target.x, simState.target.y);
  }
  Vec2 accel = getAccelerationPropDeriv(&simState, dt);
  simState.vehicle.acceleration.x = accel.x;
  simState.vehicle.acceleration.y = accel.y;

  simState.vehicle.velocity.x = simState.vehicle.velocity.x + simState.vehicle.acceleration.x * dt;
  simState.vehicle.velocity.y = simState.vehicle.velocity.y + simState.vehicle.acceleration.y * dt;

  simState.vehicle.position.x = simState.vehicle.position.x + simState.vehicle.velocity.x * dt;
  simState.vehicle.position.y = simState.vehicle.position.y + simState.vehicle.velocity.y * dt;
}

int main (int argc, char **argv) {
  seedRand();

  initRenderer(argc, argv, update, &simState);
}

