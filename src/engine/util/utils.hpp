#pragma once

#include <random>

#include "raylib.h"

namespace Engine::Utility::Random {
inline std::mt19937& get_rng() {
  static std::random_device rd;   // Initialized exactly once, first
  static std::mt19937 gen(rd());  // Initialized exactly once, second
  return gen;
}

inline float range(float min, float max) {
  std::uniform_real_distribution<float> distrib(min, max);
  return distrib(get_rng());
}

inline Vector2 inside_unit_circle() {
  Vector2 c = {range(-1, 1), range(-1, 1)};
  return c;
}
}  // namespace Engine::Utility::Random