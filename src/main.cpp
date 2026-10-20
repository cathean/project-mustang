#include "engine/core/app.hpp"

int main() {
  Core::App* app = new Core::App();
  return app->run();
}