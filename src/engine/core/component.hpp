#pragma once

#include <raylib.h>

#include <boost/uuid/uuid.hpp>
#include <cassert>

#include "gameobject.hpp"
#include "object.hpp"

namespace Engine::Core {

class GameObject;

class Component : public Object {
  friend class GameObject;

 protected:
  Component();

  void set_gameobject(GameObject* gameobject);

 public:
  virtual ~Component();

  bool enabled = true;
  GameObject* gameobject = nullptr;

  GameObject& get_gameobject();
};

}  // namespace Engine::Core