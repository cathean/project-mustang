#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

namespace Core {

class Object {
 protected:
  Object() : id_(boost::uuids::random_generator()()) {};

  virtual void start() = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
  virtual void destroy() { is_alive = false; };

 public:
  virtual ~Object() { this->destroy(); };

  bool is_alive = true;

  boost::uuids::uuid get_id();
  std::size_t get_hash();

 private:
  boost::uuids::uuid id_;
};

}  // namespace Core