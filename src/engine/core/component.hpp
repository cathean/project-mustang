#pragma once

#include <raylib.h>

#include <boost/uuid/uuid.hpp>
#include <cassert>

#include "game_object.hpp"
#include "object.hpp"

namespace Core {

class GameObject;

class Component : public Object {
  friend class GameObject;

 protected:
  Component() {};

  void start() override {}
  void update(float dt) override {}
  void draw() override {}
  void destroy() override {};
  void set_gameobject(GameObject* gameobject) { gameobject_ = gameobject; }

 public:
  virtual ~Component() = default;

  bool enabled = true;

  GameObject& get_gameobject() {
    assert(gameobject_ != nullptr);

    return *gameobject_;
  }

 private:
  GameObject* gameobject_ = nullptr;
};

}  // namespace Core