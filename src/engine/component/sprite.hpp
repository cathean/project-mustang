#pragma once

#include <raylib.h>

#include "engine/core/component.hpp"
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

  void load_texture(std::string path) { texture_ = LoadTexture(path.c_str()); }
  void load_texture(Image image) { texture_ = LoadTextureFromImage(image); }
  Texture2D get_texture() { return texture_; };

 protected:
  void start() override { load_texture(path_); }

  void draw() override {
    Rectangle rect_source =
        Rectangle{0.0, 0.0, (float)texture_.width, (float)texture_.height};
    Rectangle rect_dest = Rectangle{
        game_object->transform.position.x, game_object->transform.position.y,
        (float)texture_.width * game_object->transform.scale.x,
        (float)texture_.height * game_object->transform.scale.y};

    DrawTexturePro(texture_, rect_source, rect_dest, pivot,
                   game_object->transform.rotation, color);
  }

 private:
  std::string path_;
  Texture texture_{};
};

}  // namespace Component