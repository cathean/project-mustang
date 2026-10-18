#pragma once

#include <memory>
#include <vector>

#include "component.hpp"
#include "object.hpp"
#include "types.hpp"
#include "world.hpp"

namespace Core {

class Component;

class GameObject : public Object {
 public:
  GameObject();
  ~GameObject();

  World* world = nullptr;
  Transform2D transform{};

  template <typename T, typename... Args>
    requires std::derived_from<T, Core::Component>
  T& add_component(Args&&... args);

  template <typename T>
    requires std::derived_from<T, Core::Component>
  T* get_component();

  void update();
  void draw();
  void destroy() override;

 private:
  bool m_dead = false;
  std::vector<std::unique_ptr<Component>> m_components;
};

}  // namespace Core