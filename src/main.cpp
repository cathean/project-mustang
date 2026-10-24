#include "engine/core/app.hpp"

int main() {
  Engine::Core::App* app = new Engine::Core::App();
  return app->run();
}