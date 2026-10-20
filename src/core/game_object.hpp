#pragma once

#include <concepts>
#include <memory>
#include <vector>

#include "component.hpp"
#include "object.hpp"
#include "types.hpp"

namespace Core {

class World;

class GameObject : public Object {
  friend class World;

 protected:
  void start() override;
  void update(float dt) override;
  void draw() override;
  void destroy() override;

 public:
  GameObject();
  virtual ~GameObject();

  World* world = nullptr;
  Transform2D transform{};

  template <typename T, typename... Args>
    requires std::derived_from<T, Core::Component>
  T& add_component(Args&&... args);

  template <typename T>
    requires std::derived_from<T, Core::Component>
  T* get_component();

 private:
  std::vector<std::unique_ptr<Component>> components_;
};

}  // namespace Core