#pragma once

#include "engine/component/particle_system.hpp"
#include "engine/component/sprite.hpp"
#include "engine/core/gameobject.hpp"
#include "engine/scene_management/scene.hpp"
#include "game/scripts/player_controller.hpp"
#include "raylib.h"

namespace Mustang {
class GameplayScene : public Engine::SceneManagement::Scene {
 public:
  GameplayScene() : Engine::SceneManagement::Scene("Gameplay") {}
  ~GameplayScene() override = default;

  void on_initialize() override {
    auto p = create("Player");
    auto& sprite =
        p->add_component<::Component::Sprite>("./assets/ships/ship.png");
    sprite.debug_mode = true;

    p->add_component<Mustang::PlayerController>();
    p->transform.scale = Vector2{2, 2};

    auto x = create("ParticleTest");
    auto& particle = x->add_component<::Component::ParticleSystem>();
    particle.debug_mode = true;
    particle.emitter.rate_over_time = 0;
    particle.emitter.burst.time = 1.0f;
    particle.emitter.burst.count = 10;
    particle.shape.spawn_type = Component::BURST_SPREAD;
    particle.start_speed = {100, 100};
    x->transform.position = {200, 200};
  }

  void on_cleanup() override {}
};
}  // namespace Mustang
