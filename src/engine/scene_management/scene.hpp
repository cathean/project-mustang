#pragma once

#include <boost/uuid/uuid.hpp>
#include <memory>
#include <string>
#include <unordered_map>

#include "engine/core/game_object.hpp"
#include "engine/core/world.hpp"

namespace SceneManagement {
class Scene {
 public:
  Scene(std::string name) : name_(std::move(name)) {}
  ~Scene() {}

  bool is_loaded = false;

  std::string get_name();
  void add_world();
  void remove_world();

 private:
  std::string name_;
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<Core::World>> worlds_;
};
}  // namespace SceneManagement