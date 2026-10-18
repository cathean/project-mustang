#include "game_object.hpp"

#include <concepts>
#include <memory>

Core::GameObject::GameObject() {}

Core::GameObject::~GameObject() {
  for (auto& c : m_components) {
    c->destroy();
  }
}

void Core::GameObject::destroy() { m_dead = true; }

template <typename T, typename... Args>
  requires std::derived_from<T, Core::Component>
T& Core::GameObject::add_component(Args&&... args) {
  auto c = std::make_unique(std::forward<Args>(args)...);
  c->owner = this;
  T& ref = *c;
  m_components.push_back(std::move(c));

  return ref;
}

template <typename T>
  requires std::derived_from<T, Core::Component>
T* Core::GameObject::get_component() {
  for (auto& c : m_components) {
    if (auto* p = dynamic_cast<T*>(c.get())) {
      return p;
    }
  }

  return nullptr;
}

void Core::GameObject::update() {
  for (auto& c : m_components) {
    c->update();
  }
}

void Core::GameObject::draw() {
  for (auto& c : m_components) {
    c->draw();
  }
}