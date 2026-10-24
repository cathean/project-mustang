#include "gameobject.hpp"

#include <spdlog/spdlog.h>

#include "component.hpp"
#include "object.hpp"


Engine::Core::GameObject::GameObject(std::string name) : Object() {
  this->name = std::move(name);
}

Engine::Core::GameObject::~GameObject() {
  for (const auto& [id, c] : components_) {
    c->destroy();
  }
}

bool Engine::Core::GameObject::get_started() { return started_; }

void Engine::Core::GameObject::start() {
  for (const auto& [id, c] : components_) {
    c->start();
  }

  started_ = true;
}

void Engine::Core::GameObject::update(float dt) {
  for (const auto& [id, c] : components_) {
    c->update(dt);
  }
}

void Engine::Core::GameObject::draw() {
  for (const auto& [id, c] : components_) {
    c->draw();
  }
}