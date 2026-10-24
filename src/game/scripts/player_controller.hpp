#pragma once

#include "engine/core/component.hpp"
#include "engine/core/gameobject.hpp"
#include "raylib.h"

namespace Mustang {

class PlayerController : public Engine::Core::Component {
 public:
  PlayerController() {};

 protected:
  void start() override {}

  void update(float dt) override {
    auto mousepos = GetMousePosition();
    auto& gameobject = get_gameobject();

    gameobject.transform.position = mousepos;
  }

  void draw() override {}
};

}  // namespace Mustang