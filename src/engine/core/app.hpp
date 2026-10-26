#pragma once

#include "engine/resource_manager.hpp"
#include "engine/scene_management/scene_manager.hpp"

namespace Engine::Core {
class App {
 public:
  App()
      : scene_manager_(Engine::SceneManagement::SceneManager::get()),
        resource_manager_(Engine::ResourceManager::get()) {};

  ~App() = default;

  int run();

 private:
  Engine::SceneManagement::SceneManager& scene_manager_;
  Engine::ResourceManager& resource_manager_;

  void initialize();
  void update();
  void shutdown();
};
}  // namespace Engine::Core