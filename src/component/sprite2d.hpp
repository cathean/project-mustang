#pragma once

#include "core/component.hpp"
#include "raylib.h"
namespace Component {

class Sprite2D : public Core::Component {
 public:
  Texture2D texture;
  Color color;

 private:
};

}  // namespace Component