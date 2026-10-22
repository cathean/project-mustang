#pragma once

#include "engine/scene_management/scene_manager.hpp"

namespace Core {
class App {
 public:
  App() : scene_manager_(SceneManagement::SceneManager::get_instance()) {};

  ~App() = default;

  int run();

 private:
  SceneManagement::SceneManager& scene_manager_;

  void initialize();
  void update();
  void shutdown();
};
}  // namespace Core