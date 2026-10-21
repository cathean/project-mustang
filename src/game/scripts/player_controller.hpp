#pragma once

#include <memory>

#include "engine/core/component.hpp"
#include "engine/core/game_object.hpp"
#include "raylib.h"

namespace Mustang {

class PlayerController : public Core::Component {
 public:
  PlayerController(std::unique_ptr<Core::GameObject>& game_object)
      : Core::Component(game_object) {};

 protected:
  void update(float dt) override {
    if (IsKeyDown(KEY_RIGHT)) game_object->transform.position.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) game_object->transform.position.x -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) game_object->transform.position.y += 2.0f;
    if (IsKeyDown(KEY_UP)) game_object->transform.position.y -= 2.0f;
  }
};

}  // namespace Mustang