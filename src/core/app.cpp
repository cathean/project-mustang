
#include "app.hpp"

#include <raylib.h>

Core::App::App() {}

int Core::App::run() {
  initialize();
  update();
  shutdown();

  return 0;
}

void Core::App::initialize() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Project Mustang");
  SetTargetFPS(60);
}

void Core::App::update() {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(BLUE);
    EndDrawing();
  }
}

void Core::App::shutdown() { CloseWindow(); }