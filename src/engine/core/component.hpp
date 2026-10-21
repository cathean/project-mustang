#pragma once

#include <raylib.h>

#include <memory>

#include "game_object.hpp"
#include "object.hpp"

namespace Core {

class GameObject;

class Component : public Object {
  friend class GameObject;

 protected:
  Component(std::weak_ptr<GameObject>& gameobject) : gameobject(gameobject) {};

  void start() override {}
  void update(float dt) override {}
  void draw() override {}
  void destroy() override {};

 public:
  virtual ~Component() = default;

  bool enabled;

  GameObject& get_gameobject() { return *gameobject_.lock(); }

 private:
  std::weak_ptr<GameObject>& gameobject_;
};

}  // namespace Core