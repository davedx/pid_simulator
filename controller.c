#include "types.h"
#include "util.h"

// PID controller

const float MIN_ACCELERATION = -3.f;
const float MAX_ACCELERATION = 3.f;

/**
 * Naive controller. Jams the "stick" in whatever direction takes it towards
 * the target at max, only reducing accleration when it's right on top of the
 * target. Like how a 5 year old plays Mario Kart.
 */
Vec2 getAcceleration(SimState *simState) {
  float dx = simState->target.x - simState->vehicle.position.x;
  float dy = simState->target.y - simState->vehicle.position.y;
  Vec2 accel;
  accel.x = clampf(MIN_ACCELERATION, dx, MAX_ACCELERATION);
  accel.y = clampf(MIN_ACCELERATION, dy, MAX_ACCELERATION);
  return accel;
}
