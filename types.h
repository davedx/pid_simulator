#pragma once

struct Vec2 {
  float x;
  float y;
};

struct Vehicle {
  struct Vec2 position;
  struct Vec2 velocity;
  struct Vec2 acceleration;
};

struct SimState {
  struct Vehicle vehicle;
  struct Vec2 windSpeed;
  struct Vec2 target;
};
