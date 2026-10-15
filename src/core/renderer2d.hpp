#pragma once

#include "canvas_item.hpp"
#include "types.hpp"

namespace Core {

class Renderer2D : public CanvasItem {
 protected:
  Renderer2D();

 public:
  ~Renderer2D();

  Vector2 global_position;
  float global_rotation;
  float global_rotation_degrees;
  Vector2 global_scale;
  Transform2D transform;

 private:
};

}  // namespace Core