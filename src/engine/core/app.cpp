
#include "app.hpp"

#include <raylib.h>

#include <memory>

#include "engine/scene_management/scene_manager.hpp"
#include "game/scenes/gameplay.hpp"

int Engine::Core::App::run() {
  initialize();
  update();
  shutdown();

  return 0;
}

void Engine::Core::App::initialize() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Project Mustang");
  SetTargetFPS(60);

  scene_manager_.register_scene(std::make_unique<Mustang::GameplayScene>());
  scene_manager_.load_scene("Gameplay");
}

void Engine::Core::App::update() {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    scene_manager_.update(dt);

    BeginDrawing();
    ClearBackground(BLUE);

    scene_manager_.draw();
    EndDrawing();
  }
}

void Engine::Core::App::shutdown() {
  scene_manager_.cleanup();
  CloseWindow();
}