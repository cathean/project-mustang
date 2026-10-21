#pragma once

#include <concepts>
#include <memory>
#include <vector>

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

  World* world = nullptr;
  Transform2D transform{
      .position = Vector2Zero(), .rotation = 0, .scale = Vector2One()};

  template <typename T, typename... Args>
    requires std::derived_from<T, Core::Component>
  std::weak_ptr<T> add_component(Args&&... args) {
    std::weak_ptr<GameObject> weak_self =
        std::static_pointer_cast<GameObject>(shared_from_this());
    auto c = std::make_unique<T>(*this, std::forward<Args>(args)...);
    c->game_object = weak_self;
    T& ref = *c;
    components_.push_back(std::move(c));

    return ref;
  }

  bool get_started();

  template <typename T>
    requires std::derived_from<T, Core::Component>
  T* get_component();

 private:
  std::vector<std::unique_ptr<Component>> components_;
  bool started_ = false;
};

}  // namespace Core