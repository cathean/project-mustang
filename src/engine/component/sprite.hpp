#pragma once

#include <raylib.h>

#include "engine/core/component.hpp"
#include "engine/core/gameobject.hpp"
#include "engine/resource_manager.hpp"
#include "raylib.h"

namespace Component {

class Sprite : public Engine::Core::Component {
 public:
  Sprite(std::string path) : path_(std::move(path)) {}
  ~Sprite() = default;

  Shader shader{};
  Rectangle rect{};
  Color color = WHITE;
  Vector2 pivot{0.5, 0.5};
  bool debug_mode = false;

  void load_texture(const std::string& path) {
    path_ = path;
    texture_ = &resource_manager_.tryget_texture(path_);
  }
  Texture2D get_texture() { return *texture_; };

 protected:
  void start() override { load_texture(path_); }

  void update(float dt) override {
    rect_source = {0.0, 0.0, (float)texture_->width, (float)texture_->height};
    rect_dest = {gameobject->transform.position.x,
                 gameobject->transform.position.y,
                 (float)texture_->width * gameobject->transform.scale.x,
                 (float)texture_->height * gameobject->transform.scale.y};
    origin_offset = {
        texture_->width * gameobject->transform.scale.x * pivot.x,
        texture_->height * gameobject->transform.scale.y * pivot.y};
    rect = {rect_dest.x - origin_offset.x, rect_dest.y - origin_offset.y,
            rect_dest.width, rect_dest.height};
  }

  void draw() override {
    if (texture_ == nullptr) return;

    DrawTexturePro(*texture_, rect_source, rect_dest, origin_offset,
                   gameobject->transform.rotation, color);

    if (debug_mode) {
      DrawText(gameobject->name.c_str(), rect.x, rect.y - 14, 12, RED);
      DrawRectangleLinesEx(rect, 1, RED);
    }
  }

 private:
  Engine::ResourceManager& resource_manager_ = Engine::ResourceManager::get();
  std::string path_{};
  Texture* texture_ = nullptr;

  Rectangle rect_source{};
  Rectangle rect_dest{};
  Vector2 origin_offset{};
};

}  // namespace Component
