#include "scene_manager.hpp"

#include <memory>

#include "scene.hpp"

Engine::SceneManagement::SceneManager::SceneManager() = default;
Engine::SceneManagement::SceneManager::~SceneManager() = default;

Engine::SceneManagement::Scene&
Engine::SceneManagement::SceneManager::register_scene(
    std::unique_ptr<Scene> scene) {
  auto [it, inserted] =
      scenes_.try_emplace(scene->get_name(), std::move(scene));
  if (!inserted) {
    throw std::runtime_error("Scene already exist!");
  }

  return *it->second;
}

void Engine::SceneManagement::SceneManager::load_scene(std::string name) {
  auto it = scenes_.find(name);

  if (it != scenes_.end()) {
    current_scene_ = it->second.get();
  }
}

void Engine::SceneManagement::SceneManager::update(float dt) {
  if (current_scene_ == nullptr) {
    return;
  }

  if (!current_scene_->is_initialized_) {
    current_scene_->initialize();
  }

  current_scene_->update(dt);
}

void Engine::SceneManagement::SceneManager::draw() {
  if (current_scene_ == nullptr) {
    return;
  }

  current_scene_->draw();
}

void Engine::SceneManagement::SceneManager::cleanup() {
  if (current_scene_ == nullptr) {
    return;
  }

  current_scene_->cleanup();
}