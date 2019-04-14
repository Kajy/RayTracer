cmake_minimum_required(VERSION 3.11)
project(RT)

macro(print_all_variables)
	message(STATUS "print_all_variables------------------------------------------{")
	get_cmake_property(_variableNames VARIABLES)
	foreach (_variableName ${_variableNames})
		message(STATUS "${_variableName}=${${_variableName}}")
	endforeach()
	message(STATUS "print_all_variables------------------------------------------}")
endmacro()

set(CMAKE_CXX_STANDARD 17)

function(setupWindows)
	set(CMAKE_MODULE_PATH "C:/Program Files/CMake/modules")
	set(SDL2_PATH "C:/Libraries/SDL")

	find_package(SDL2 REQUIRED)

	print_all_variables()

	include_directories(${SDL2_INCLUDE_DIR})
	include_directories(${PROJECT_SOURCE_DIR}/src)

	add_executable(RT
			src/main.cpp
			src/RayTracer/RayTracer.hpp
			src/RayTracer/RayTracer.cpp
			src/Window/Window.hpp src/Window/Window.cpp
			src/Config/config.hpp
			src/EventHandler/EventHandler.hpp
			src/EventHandler/EventHandler.cpp
			src/Debug/Debug.hpp
			src/Camera/Camera.cpp
			src/Scene/Scene.cpp
			src/SphereObject/SphereObject.cpp)

	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
	target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIBRARY})
endfunction()

function(setupLinux)
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS})
	include_directories(${PROJECT_SOURCE_DIR}/src)
	find_package(glm REQUIRED)
	add_executable(RT
			src/main.cpp
			src/RayTracer/RayTracer.hpp
			src/RayTracer/RayTracer.cpp
			src/Window/Window.hpp
			src/Window/Window.cpp
			src/Config/config.hpp
			src/EventHandler/EventHandler.hpp
			src/EventHandler/EventHandler.cpp
			src/Debug/Debug.hpp
			src/Scene/Scene.cpp
			src/Scene/Scene.hpp
			src/SphereObject/SphereObject.cpp
			src/SphereObject/SphereObject.hpp
			src/Camera/Camera.cpp
			src/Camera/Camera.hpp
			)

	string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} glm)
endfunction()

if (WIN32)
	setupWindows()
else (WIN32)
	setupLinux()
endif(WIN32)