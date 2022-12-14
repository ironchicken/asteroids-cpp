cmake_minimum_required(VERSION 3.22)

project(asteroids)

set(simple_VERSION_MAJOR 0)
set(simple_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
  asteroids
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  )

add_executable(
  asteroids
  ${CMAKE_SOURCE_DIR}/asteroids.cpp
  ${CMAKE_SOURCE_DIR}/src/Vector2.hpp
  ${CMAKE_SOURCE_DIR}/src/Component.cpp
  ${CMAKE_SOURCE_DIR}/src/Actor.cpp
  ${CMAKE_SOURCE_DIR}/src/SpriteComponent.cpp
  ${CMAKE_SOURCE_DIR}/src/Game.cpp
  )

target_include_directories(
  asteroids PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  )

target_link_libraries(
  asteroids
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  )
