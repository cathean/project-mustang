#pragma once

#include <algorithm>
#include <memory>

#include "game_object.hpp"

namespace Core {

class World {
 public:
  World();
  ~World();

  GameObject& create() {
    game_objects_.push_back(std::make_unique<GameObject>());
    game_objects_.back()->world = this;
    return *game_objects_.back();
  }

  void update(float dt) {
    for (size_t i = 0; i < game_objects_.size(); i++) {
      game_objects_[i]->start();
    }

    for (size_t i = 0; i < game_objects_.size(); i++) {
      game_objects_[i]->update(dt);
    }

    game_objects_.erase(
        std::remove_if(game_objects_.begin(), game_objects_.end(),
                       [](auto& go) { return !go->is_alive; }),
        game_objects_.end());
  }

  void draw() {
    for (auto& go : game_objects_) {
      go->draw();
    }
  }

 private:
  std::vector<std::unique_ptr<GameObject>> game_objects_;
};

}  // namespace Core