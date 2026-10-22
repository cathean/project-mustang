#pragma once

#include <string>
#include <unordered_map>

#include "scene.hpp"

namespace SceneManagement {

class SceneManager {
 public:
  ~SceneManager();

  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

  static SceneManager& get_instance() {
    static SceneManager instance;
    return instance;
  }

  static void register_scene(Scene* scene) {
    auto [it, inserted] =
        scenes_.try_emplace(scene->get_name(), std::move(scene));

    if (!inserted) {
      throw std::runtime_error("Scene already exist!");
    }
  }

  static Scene get_current_scene() { return current_scene_; }

  static void start() {}
  static void update(float dt) {}
  static void draw() {}
  static void cleanup() {}

 private:
  SceneManager();

  static Scene current_scene_;
  static std::unordered_map<std::string, std::unique_ptr<Scene>> scenes_;
};

}  // namespace SceneManagement