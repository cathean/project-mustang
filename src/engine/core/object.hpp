#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

namespace Engine::Core {

class Object {
 protected:
  Object() : id_(boost::uuids::random_generator()()) {};

  virtual void start() = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
  virtual void destroy() { is_alive = false; };

 public:
  virtual ~Object() = default;

  bool is_alive = true;
  std::string name = "";

  boost::uuids::uuid get_id() { return id_; }

  static void free(Object& object) { object.destroy(); }

 private:
  boost::uuids::uuid id_;
};

}  // namespace Engine::Core