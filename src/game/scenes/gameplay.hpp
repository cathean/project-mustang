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
    auto player = create("Player");
    auto& sprite =
        player->add_component<::Component::Sprite>("./assets/ships/ship.png");
    sprite.debug_mode = true;

    player->add_component<Mustang::PlayerController>();
    player->local_transform.scale = {2, 2};

    auto x = player->add_child("ParticleTest");
    auto& particle = x->add_component<::Component::ParticleSystem>();
    particle.debug_mode = true;
    particle.emitter.rate_over_time = 0;
    particle.emitter.burst.time = 1.0f;
    particle.emitter.burst.count = 10;
    particle.shape.spawn_type = Component::BURST_SPREAD;
    particle.start_speed = {100, 100};
    particle.lifetime = 1.0f;
    particle.size_over_lifetime.enable = true;
    particle.size_over_lifetime.start_value = 20.0f;
    particle.size_over_lifetime.end_value = 0.0f;
    particle.size_over_lifetime.duration = particle.lifetime;
    particle.size_over_lifetime.ease_func = EaseQuadIn;
  }

  void on_cleanup() override {}
};
}  // namespace Mustang
