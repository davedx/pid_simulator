#include "types.h"
#include "util.h"

// PID controller

const float MIN_ACCELERATION = -3.f;
const float MAX_ACCELERATION = 3.f;

vec2 getAcceleration(struct SimState *simState) {
  float dx = simState->target.x - simState->vehicle.position.x;
  float dy = simState->target.y - simState->vehicle.position.y;
  vec2 accel;
  accel.x = clampf(MIN_ACCELERATION, dx, MAX_ACCELERATION);
  accel.y = clampf(MIN_ACCELERATION, dy, MAX_ACCELERATION);
  return accel;
}
