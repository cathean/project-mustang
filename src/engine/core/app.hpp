#pragma once

#include "engine/scene_management/scene_manager.hpp"

namespace Engine::Core {
class App {
 public:
  App() = default;

  ~App() = default;

  int run();

 private:
  Engine::SceneManagement::SceneManager scene_manager_;

  void initialize();
  void update();
  void shutdown();
};
}  // namespace Engine::Core