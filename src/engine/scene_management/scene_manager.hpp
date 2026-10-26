#pragma once

#include <map>
#include <memory>

namespace Engine::SceneManagement {

class Scene;

class SceneManager {
 public:
  static SceneManager& get() {
    static SceneManager instance;
    return instance;
  }

  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

  Scene& register_scene(std::unique_ptr<Scene> scene);
  void load_scene(const std::string& name);
  void load_scene(int index);

  void update(float dt);
  void draw();
  void cleanup();

 private:
  SceneManager();
  ~SceneManager();

  std::map<std::string, std::unique_ptr<Scene>> scenes_;
  Scene* current_scene_;
};

}  // namespace Engine::SceneManagement