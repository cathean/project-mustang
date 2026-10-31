#pragma once

#include <memory>
#include <random>
#include <unordered_map>

#include "engine/core/gameobject.hpp"
#include "engine/scene_management/scene.hpp"
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

namespace Engine::Utility {
inline Core::GameObject* create_gameobject(
    SceneManagement::Scene* scene, std::string name,
    std::unordered_map<boost::uuids::uuid, std::unique_ptr<Core::GameObject>>*
        arr) {
  auto go = std::make_unique<Core::GameObject>(std::move(name));
  auto id = go->get_id();
  go->scene = scene;

  auto [it, inserted] = arr->try_emplace(id, std::move(go));
  if (!inserted) {
    return nullptr;
  }

  return it->second.get();
}
}  // namespace Engine::Utility