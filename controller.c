#include <math.h>

#include "types.h"
#include "util.h"
#include "macros.h"
#include "controller.h"

// PID controller

const float MIN_ACCELERATION = -5.f;
const float MAX_ACCELERATION = 5.f;

const float PROPORTION_CONSTANT = 2.f;
const float INTEGRAL_CONSTANT = 0.1f;
const float DERIVATIVE_CONSTANT = 3.f;

/**
 * Naive controller. Jams the "stick" in whatever direction takes it towards
 * the target at max, only reducing accleration when it's right on top of the
 * target. Like how a 5 year old plays Mario Kart.
 */
Vec2 getAcceleration(SimState *simState) {
  float dx = simState->target.x > simState->vehicle.position.x ? MAX_ACCELERATION : MIN_ACCELERATION;
  float dy = simState->target.y > simState->vehicle.position.y ? MAX_ACCELERATION : MIN_ACCELERATION;
  Vec2 accel;
  accel.x = clampf(MIN_ACCELERATION, dx, MAX_ACCELERATION);
  accel.y = clampf(MIN_ACCELERATION, dy, MAX_ACCELERATION);
  return accel;
}

/**
 * Proportional acceleration controller.
 */
Vec2 getAccelerationProp(SimState *simState) {
  float dx = simState->target.x - simState->vehicle.position.x;
  float dy = simState->target.y - simState->vehicle.position.y;
  dx *= PROPORTION_CONSTANT;
  dy *= PROPORTION_CONSTANT;
  Vec2 accel;
  accel.x = clampf(MIN_ACCELERATION, dx, MAX_ACCELERATION);
  accel.y = clampf(MIN_ACCELERATION, dy, MAX_ACCELERATION);
  return accel;
}

/**
 * Proportional derivative acceleration controller.
 */
float lastErrX = 0;
float lastErrY = 0;
Vec2 getAccelerationPropDeriv(SimState *simState, float deltaTime) {
  float errX = simState->target.x - simState->vehicle.position.x;
  float errY = simState->target.y - simState->vehicle.position.y;

  float derivX = (errX - lastErrX) * (DERIVATIVE_CONSTANT / deltaTime);
  float derivY = (errY - lastErrY) * (DERIVATIVE_CONSTANT / deltaTime);

  float propX = errX * PROPORTION_CONSTANT;
  float propY = errY * PROPORTION_CONSTANT;

  lastErrX = errX;
  lastErrY = errY;

  errX = propX + derivX;
  errY = propY + derivY;

  Vec2 accel;
  accel.x = clampf(MIN_ACCELERATION, errX, MAX_ACCELERATION);
  accel.y = clampf(MIN_ACCELERATION, errY, MAX_ACCELERATION);
  return accel;
}

/**
 * Proportional integral derivative acceleration controller.
 * Rewritten following JPL rule of 10.
 */
float errSumX = 0;
float errSumY = 0;
int getAccelerationPropIntegDeriv(SimState *simState, float deltaTime, Vec2 *accel) {
  if (!c_assert_float(deltaTime, 0, 1.f)) {
    return ERROR;
  }
  if (!c_assert_vec2(simState->vehicle.position, -1000.f, 1000.f)) {
    return ERROR;
  }
  if (!c_assert_vec2(simState->target, -1000.f, 1000.f)) {
    return ERROR;
  }

  float errX = simState->target.x - simState->vehicle.position.x;
  float errY = simState->target.y - simState->vehicle.position.y;

  float derivX = (errX - lastErrX) * (DERIVATIVE_CONSTANT / deltaTime);
  float derivY = (errY - lastErrY) * (DERIVATIVE_CONSTANT / deltaTime);

  float propX = errX * PROPORTION_CONSTANT;
  float propY = errY * PROPORTION_CONSTANT;

  lastErrX = errX;
  lastErrY = errY;

  float intErrX = errX * deltaTime;
  float intErrY = errY * deltaTime;
  errSumX += intErrX;
  errSumY += intErrY;
  float integX = errSumX * INTEGRAL_CONSTANT;
  float integY = errSumY * INTEGRAL_CONSTANT;

  errX = propX + derivX + integX;
  errY = propY + derivY + integY;

  accel->x = clampf(MIN_ACCELERATION, errX, MAX_ACCELERATION);
  accel->y = clampf(MIN_ACCELERATION, errY, MAX_ACCELERATION);
  return OK;
}