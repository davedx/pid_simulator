#include "types.h"

Vec2 getAcceleration(SimState *simState);
Vec2 getAccelerationProp(SimState *simState);
Vec2 getAccelerationPropDeriv(SimState *simState, float deltaTime);
Vec2 getAccelerationPropIntegDeriv(SimState *simState, float deltaTime);
