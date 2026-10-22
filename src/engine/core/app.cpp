
#include "app.hpp"

#include <raylib.h>

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
    scene_manager_.update(dt);

    BeginDrawing();
    ClearBackground(BLUE);

    scene_manager_.draw();
    EndDrawing();
  }
}

void Core::App::shutdown() {
  scene_manager_.cleanup();
  CloseWindow();
}