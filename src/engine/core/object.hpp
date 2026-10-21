#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <memory>

namespace Core {

class Object : public std::enable_shared_from_this<Object> {
 protected:
  Object() : id_(boost::uuids::random_generator()()) {};

  virtual void start() = 0;
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
  virtual void destroy() { is_alive = false; };

 public:
  virtual ~Object() { this->destroy(); };

  bool is_alive = true;
  std::string name = "";

  boost::uuids::uuid get_id();
  std::size_t get_hash();

  static void destroy(Object& object) { object.destroy(); }

 private:
  boost::uuids::uuid id_;
};

}  // namespace Core