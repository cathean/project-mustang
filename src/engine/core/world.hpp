#pragma once

#include <memory>
#include <unordered_map>

#include "game_object.hpp"

namespace Core {

class World {
 public:
  World() : id_(boost::uuids::random_generator()()) {};
  ~World() {};

  GameObject* create(std::string name) {
    auto go = std::make_unique<GameObject>(std::move(name));
    auto id = go->get_id();
    go->world = this;

    auto [it, inserted] = gameobjects_.try_emplace(id, std::move(go));
    if (!inserted) {
      return nullptr;
    }

    return it->second.get();
  }

  void update(float dt) {
    for (const auto& [id, go] : gameobjects_) {
      if (!go->get_started()) {
        go->start();
      }
    }

    for (const auto& [id, go] : gameobjects_) {
      go->update(dt);
    }

    std::erase_if(gameobjects_,
                  [](const auto& pair) { return !pair.second->is_alive; });
  }

  void draw() {
    for (const auto& [id, go] : gameobjects_) {
      go->draw();
    }
  }

  boost::uuids::uuid get_id() { return id_; }

 private:
  boost::uuids::uuid id_;
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<GameObject>>
      gameobjects_;
};

}  // namespace Core