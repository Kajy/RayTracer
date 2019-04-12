cmake_minimum_required(VERSION 3.13)
project(RT)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(RT src/main.cpp src/RayTracer/RayTracer.hpp src/RayTracer/RayTracer.cpp src/Window/Window.hpp src/Window/Window.cpp src/Config/config.hpp src/EventHandler/EventHandler.hpp src/EventHandler/EventHandler.cpp src/Debug/Debug.hpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})