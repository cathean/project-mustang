#pragma once

#include <memory>
#include <string>
#include <vector>

#include "engine/core/game_object.hpp"

namespace SceneManagement {
class Scene {
 public:
  Scene(std::string name) : name(std::move(name)) {}
  ~Scene() {}

  std::string name{};
  bool is_loaded = false;

  std::vector<std::unique_ptr<Core::GameObject>>& get_all_root_gameobjects() {
    return game_objects_;
  }

 private:
  std::vector<std::unique_ptr<Core::GameObject>> game_objects_;
};
}  // namespace SceneManagement