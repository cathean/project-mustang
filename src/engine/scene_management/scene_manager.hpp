#pragma once

#include <map>
#include <memory>

namespace Engine::SceneManagement {

class Scene;

class SceneManager {
 public:
  SceneManager();
  ~SceneManager();

  Scene& register_scene(std::unique_ptr<Scene> scene);
  void load_scene(std::string name);
  void load_scene(int index);

  void update(float dt);
  void draw();
  void cleanup();

 private:
  std::map<std::string, std::unique_ptr<Scene>> scenes_;
  Scene* current_scene_;
};

}  // namespace Engine::SceneManagement