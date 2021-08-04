#include "types.h"

#define OK 0
#define ERROR -1

Vec2 getAcceleration(SimState *simState);
Vec2 getAccelerationProp(SimState *simState);
Vec2 getAccelerationPropDeriv(SimState *simState, float deltaTime);
int getAccelerationPropIntegDeriv(SimState *simState, float deltaTime, Vec2 *accel);
