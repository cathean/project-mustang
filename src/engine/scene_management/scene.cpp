#include "scene.hpp"

#include "engine/core/gameobject.hpp"

Engine::SceneManagement::Scene::Scene(std::string name)
    : name_(std::move(name)), id_(boost::uuids::random_generator()()) {};
Engine::SceneManagement::Scene::~Scene() = default;

std::string Engine::SceneManagement::Scene::get_name() { return name_; }

Engine::Core::GameObject* Engine::SceneManagement::Scene::create(
    std::string name) {
  auto go = std::make_unique<Core::GameObject>(std::move(name));
  auto id = go->get_id();
  go->scene = this;

  auto [it, inserted] = gameobjects_.try_emplace(id, std::move(go));
  if (!inserted) {
    return nullptr;
  }

  return it->second.get();
}

void Engine::SceneManagement::Scene::initialize() { is_initialized_ = true; }

void Engine::SceneManagement::Scene::update(float dt) {
  for (const auto& [id, go] : gameobjects_) {
    if (!go->get_started()) {
      go->start();
    }
  }

  for (const auto& [id, go] : gameobjects_) {
    go->update(dt);
  }

  std::erase_if(gameobjects_,
                [](const auto& pair) { return !pair.second->is_alive; });
}

void Engine::SceneManagement::Scene::draw() {
  for (const auto& [id, go] : gameobjects_) {
    go->draw();
  }
}