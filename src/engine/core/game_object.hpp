#pragma once

#include <concepts>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "component.hpp"
#include "object.hpp"
#include "raymath.h"
#include "types.hpp"

namespace Core {

class Component;
class World;

class GameObject : public Object {
  friend class World;

 protected:
  void start() override;
  void update(float dt) override;
  void draw() override;

 public:
  GameObject(std::string name);
  virtual ~GameObject();

  GameObject(const GameObject&) = delete;
  GameObject& operator=(const GameObject&) = delete;

  World* world = nullptr;
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

  // template <typename T>
  //   requires std::derived_from<T, Core::Component>
  // T* get_component() {};

 private:
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<Component>>
      components_;

  bool started_ = false;
};

}  // namespace Core