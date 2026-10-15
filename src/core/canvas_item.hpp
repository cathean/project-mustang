#pragma once

#include <raylib.h>

#include "component.hpp"

namespace Core {

class CanvasItem : public Component {
 protected:
  CanvasItem() {}

 public:
  ~CanvasItem() {}

  Rectangle bound;
  Color color;
  Material material;
  int sort_order;

 private:
};

}  // namespace Core