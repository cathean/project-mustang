
#include "app.hpp"

#include <raylib.h>

#include "engine/component/sprite.hpp"
#include "game/scripts/player_controller.hpp"
#include "world.hpp"

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

  // NOTE: TEST CASE
  world = std::make_unique<World>();
  auto& test = world->create("test");
  test.add_component<::Component::Sprite>("duck.jpg");
  test.transform.scale = Vector2{0.2, 0.2};
  test.add_component<::Mustang::PlayerController>();
}

void Core::App::update() {
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    world->update(dt);

    BeginDrawing();
    ClearBackground(BLUE);

    world->draw();
    EndDrawing();
  }
}

void Core::App::shutdown() { CloseWindow(); }