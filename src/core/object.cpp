#include "object.hpp"

#include <boost/uuid/uuid_generators.hpp>

Core::Object::Object() : m_id(boost::uuids::random_generator()()) {}