#pragma once

#include <raylib.h>

typedef struct Transform2D {
  Vector2 position;     // Translation
  Quaternion rotation;  // Rotation
  Vector2 scale;        // Scale
} Transform2D;