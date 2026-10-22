#include "game_object.hpp"

#include <spdlog/spdlog.h>

Core::GameObject::GameObject(std::string name) { this->name = std::move(name); }

Core::GameObject::~GameObject() {
  for (const auto& [id, c] : components_) {
    c->destroy();
  }
}

bool Core::GameObject::get_started() { return started_; }

void Core::GameObject::start() {
  for (const auto& [id, c] : components_) {
    c->start();
  }

  started_ = true;
}

void Core::GameObject::update(float dt) {
  for (const auto& [id, c] : components_) {
    c->update(dt);
  }
}

void Core::GameObject::draw() {
  for (const auto& [id, c] : components_) {
    c->draw();
  }
}