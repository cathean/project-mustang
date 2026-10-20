#pragma once

#include <raylib.h>

#include "core/component.hpp"
#include "raylib.h"
#include "raymath.h"

namespace Component {

class Sprite : public Core::Component {
 public:
  Sprite(std::string path) : path_(std::move(path)) {}
  ~Sprite() { UnloadTexture(texture_); }

  Color color = WHITE;
  bool flip_h = false;
  bool flip_v = false;
  Vector2 pivot = Vector2Zero();
  Rectangle rect{};

  void load_texture(std::string path) { texture_ = LoadTexture(path.c_str()); }
  void load_texture(Image image) { texture_ = LoadTextureFromImage(image); }
  Texture2D get_texture() { return texture_; };

 protected:
  void start() override { load_texture(path_); }
  void draw() override {
    DrawTextureEx(texture_, game_object->transform.position,
                  game_object->transform.rotation, game_object->transform.scale,
                  color);
  }

 private:
  std::string path_;
  Texture texture_{};
};

}  // namespace Component