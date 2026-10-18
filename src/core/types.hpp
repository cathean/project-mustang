#pragma once

#include <raylib.h>

typedef struct Transform2D {
  Vector2 position;
  Quaternion rotation;
  Vector2 scale;
} Transform2D;