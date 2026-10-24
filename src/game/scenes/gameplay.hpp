#pragma once

#include "engine/component/sprite.hpp"
#include "engine/core/gameobject.hpp"
#include "engine/scene_management/scene.hpp"
#include "game/scripts/player_controller.hpp"

namespace Mustang {
class GameplayScene : public Engine::SceneManagement::Scene {
 public:
  GameplayScene() : Engine::SceneManagement::Scene("Gameplay") {}
  ~GameplayScene() override = default;

  void initialize() override {
    auto p = create("Player");
    p->add_component<::Component::Sprite>("parrots.png");
    p->add_component<Mustang::PlayerController>();

    Engine::SceneManagement::Scene::initialize();
  }

  void cleanup() override {}
};
}  // namespace Mustang