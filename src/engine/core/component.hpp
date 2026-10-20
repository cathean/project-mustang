#pragma once

#include <raylib.h>

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

 public:
  virtual ~Component() = default;

  bool enabled;
  GameObject* game_object = nullptr;

 private:
};

}  // namespace Core