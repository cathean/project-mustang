#include "game_object.hpp"

#include <concepts>
#include <memory>

Core::GameObject::GameObject() {}

Core::GameObject::~GameObject() {
  for (auto& c : components_) {
    c->destroy();
  }
}

template <typename T, typename... Args>
  requires std::derived_from<T, Core::Component>
T& Core::GameObject::add_component(Args&&... args) {
  auto c = std::make_unique<T>(std::forward<Args>(args)...);
  c->owner = this;
  T& ref = *c;
  components_.push_back(std::move(c));

  return ref;
}

template <typename T>
  requires std::derived_from<T, Core::Component>
T* Core::GameObject::get_component() {
  for (auto& c : components_) {
    if (auto* p = dynamic_cast<T*>(c.get())) {
      return p;
    }
  }

  return nullptr;
}

void Core::GameObject::start() {
  for (auto& c : components_) {
    c->start();
  }
}

void Core::GameObject::update(float dt) {
  for (auto& c : components_) {
    c->update(dt);
  }
}

void Core::GameObject::draw() {
  for (auto& c : components_) {
    c->draw();
  }
}