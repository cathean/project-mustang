#pragma once

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
  }

  void on_cleanup() override {}
};
}  // namespace Mustang
