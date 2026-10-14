cmake_minimum_required(VERSION 3.10.0)
project(game_mustang LANGUAGES C CXX)

set(cmake_cxx_standard 17)
set(cmake_cxx_standard_required on)
set(cmake_export_compile_commands on)

find_package(raylib REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS filesystem)

add_executable(game_mustang
  src/main.cpp
  src/core/object.cpp
)

target_include_directories(game_mustang PRIVATE
  src/

  ${Boost_INCLUDE_DIRS}
)

set_target_properties(game_mustang PROPERTIES
  OUTPUT_NAME "mustang"
  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
)

target_link_libraries(game_mustang PRIVATE
  raylib
  spdlog
  Boost::filesystem
)