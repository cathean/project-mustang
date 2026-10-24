#pragma once

#include <unordered_map>

#include "engine/core/types.hpp"
#include "object.hpp"
#include "raymath.h"

namespace Engine::SceneManagement {
class Scene;
}

namespace Engine::Core {

class Component;

class GameObject : public Object {
  friend class Engine::SceneManagement::Scene;

 protected:
  void start() override;
  void update(float dt) override;
  void draw() override;

 public:
  GameObject(std::string name);
  virtual ~GameObject();

  GameObject(const GameObject&) = delete;
  GameObject& operator=(const GameObject&) = delete;

  SceneManagement::Scene* scene = nullptr;
  Transform2D transform{
      .position = Vector2Zero(), .rotation = 0, .scale = Vector2One()};

  template <typename T, typename... Args>
    requires std::derived_from<T, Core::Component>
  T& add_component(Args&&... args) {
    auto c = std::make_unique<T>(std::forward<Args>(args)...);
    c->set_gameobject(this);
    auto id = c->get_id();

    auto [it, inserted] = components_.try_emplace(id, std::move(c));
    if (!inserted) {
      throw std::runtime_error("Component already exist!");
    }

    return *static_cast<T*>(it->second.get());
  }

  bool get_started();

 private:
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<Component>>
      components_;

  bool started_ = false;
};

}  // namespace Engine::Core