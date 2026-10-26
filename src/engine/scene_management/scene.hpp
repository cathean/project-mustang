#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <string>
#include <unordered_map>

#include "scene_manager.hpp"

namespace Engine::Core {
class GameObject;
}

namespace Engine::SceneManagement {
class Scene {
  friend class SceneManager;

 public:
  explicit Scene(std::string name);
  virtual ~Scene();

  bool is_loaded = false;

  std::string get_name();
  Core::GameObject* create(std::string name);

 protected:
  virtual void on_initialize() {};
  virtual void on_cleanup() {};

 private:
  boost::uuids::uuid id_;
  std::string name_;
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<Core::GameObject>>
      gameobjects_;
  bool is_initialized_ = false;
  bool is_pending_loading_ = false;

  void initialize();
  void update(float dt);
  void draw();
  void cleanup();
};
}  // namespace Engine::SceneManagement
