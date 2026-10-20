#pragma once

#include <memory>

#include "world.hpp"

namespace Core {
class App {
 public:
  App();

  ~App() = default;

  int run();

 private:
  std::unique_ptr<World> world;

  void initialize();
  void update();
  void shutdown();
};
}  // namespace Core