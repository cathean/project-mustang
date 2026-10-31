#include "gameobject.hpp"

#include <spdlog/spdlog.h>

#include "component.hpp"
#include "engine/util/utils.hpp"
#include "object.hpp"
#include "raymath.h"

Engine::Core::GameObject::GameObject(std::string name) : Object() {
  this->name = std::move(name);
}

Engine::Core::GameObject::~GameObject() {
  for (const auto& [id, c] : components_) {
    c->destroy();
  }
}

Engine::Core::GameObject* Engine::Core::GameObject::add_child(
    std::string name) {
  auto child = Utility::create_gameobject(this->scene, name, &childs_);
  child->parent = this;
  return child;
}

bool Engine::Core::GameObject::is_already_started() { return started_; }

void Engine::Core::GameObject::start() {
  for (const auto& [id, child] : childs_) {
    child->start();
  }

  for (const auto& [id, c] : components_) {
    c->start();
  }

  started_ = true;
}

void Engine::Core::GameObject::update(float dt) {
  if (parent != nullptr) {
    transform.position = parent->transform.position + local_transform.position;
    transform.scale = parent->transform.scale * local_transform.scale;
    transform.rotation = parent->transform.rotation + local_transform.rotation;
  }

  for (const auto& [id, child] : childs_) {
    child->update(dt);
  }

  for (const auto& [id, c] : components_) {
    c->update(dt);
  }
}

void Engine::Core::GameObject::draw() {
  for (const auto& [id, child] : childs_) {
    child->draw();
  }

  for (const auto& [id, c] : components_) {
    c->draw();
  }
}