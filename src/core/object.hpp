#pragma once

#include <boost/uuid/uuid.hpp>
#include <string>

namespace Core {

class Object {
 protected:
  Object();

 public:
  virtual ~Object() = default;

  std::string name;

  boost::uuids::uuid get_id();
  std::size_t get_hash();
  std::string to_string();

  virtual void destroy() = 0;

 private:
  boost::uuids::uuid m_id;
};

}  // namespace Core