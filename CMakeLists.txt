cmake_minimum_required(VERSION 3.10.0)
project(game_mustang LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


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

set(SUPPORT_TRACELOG OFF CACHE INTERNAL "Disable raylib trace logs")

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.17.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(spdlog)

find_package(Boost CONFIG REQUIRED COMPONENTS filesystem)

add_executable(game_mustang
  src/main.cpp
  src/engine/core/app.cpp
  src/engine/core/gameobject.cpp
  src/engine/core/component.cpp
  src/engine/scene_management/scene.cpp
  src/engine/scene_management/scene_manager.cpp
)

target_include_directories(game_mustang PRIVATE
  src/
  ${Boost_INCLUDE_DIRS}
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
