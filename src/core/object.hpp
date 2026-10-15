#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <string>

namespace Core {

class Object {
 protected:
  Object() : m_id(boost::uuids::random_generator()()) {}

 public:
  ~Object() {}

  std::string name;

  boost::uuids::uuid get_id();
  std::size_t get_hash();
  std::string to_string();

  static void instantiate(Object object);
  static void destroy(Object object);

 private:
  boost::uuids::uuid m_id;
};

}  // namespace Core