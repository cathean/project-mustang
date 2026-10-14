#ifndef OBJECT_H
#define OBJECT_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>

namespace Core {

class Object {
 public:
  Object() : id_(boost::uuids::random_generator()()) {}

  ~Object() {}

  std::string name;

  boost::uuids::uuid get_id();

 private:
  boost::uuids::uuid id_;
};

}  // namespace Core

#endif