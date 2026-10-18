cmake_minimum_required(VERSION 3.10.0)
project(game_mustang LANGUAGES C CXX)

set(cmake_cxx_standard 17)
set(cmake_cxx_standard_required on)
set(cmake_export_compile_commands on)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)
find_package(spdlog REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS filesystem)

add_executable(game_mustang
  src/main.cpp
  src/core/object.cpp
  src/core/component.cpp
  src/core/app.cpp
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
  spdlog::spdlog
  Boost::filesystem
)

# Statically link libgcc and libstdc++ for GCC or Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_options(game_mustang PRIVATE 
    "-static-libgcc" 
    "-static-libstdc++"
    "-Wl,-Bstatic,--whole-archive" "-lwinpthread" "-Wl,--no-whole-archive"
)
endif()