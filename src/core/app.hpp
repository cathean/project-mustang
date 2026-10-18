#pragma once

namespace Core {
class App {
 public:
  App();

  ~App() = default;

  int run();

 private:
  void initialize();
  void update();
  void shutdown();
};
}  // namespace Core