#include "component.hpp"

#include <cassert>

#include "gameobject.hpp"

Engine::Core::Component::Component() = default;
Engine::Core::Component::~Component() = default;

void Engine::Core::Component::set_gameobject(
    Engine::Core::GameObject* gameobject) {
  gameobject_ = gameobject;
}

Engine::Core::GameObject& Engine::Core::Component::get_gameobject() {
  assert(gameobject_ != nullptr);

  return *gameobject_;
}