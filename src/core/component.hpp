#pragma once

#include <raylib.h>

#include "game_object.hpp"
#include "object.hpp"

namespace Core {

class GameObject;

class Component : public Object {
 protected:
  Component() {};

 public:
  virtual ~Component() = default;

  bool enabled;
  GameObject* owner = nullptr;

  virtual void start() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;

 private:
  bool m_started = false;
};

}  // namespace Core