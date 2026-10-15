#pragma once

#include <raylib.h>

#include "object.hpp"

namespace Core {
class Component : public Object {
 protected:
  Component() {}

 public:
  ~Component() {}

  bool enabled;

  virtual void on_enter();
  virtual void on_exit();
  virtual void on_destroy();
  virtual void start();
  virtual void update();

 private:
};

}  // namespace Core