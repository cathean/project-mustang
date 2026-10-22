#pragma once

#include "engine/core/component.hpp"
#include "engine/core/game_object.hpp"
#include "raylib.h"

namespace Mustang {

class PlayerController : public Core::Component {
 public:
  PlayerController() {};

 protected:
  void update(float dt) override {
    auto mousepos = GetMousePosition();
    auto& gameobject = get_gameobject();

    gameobject.transform.position = mousepos;
  }
};

}  // namespace Mustang