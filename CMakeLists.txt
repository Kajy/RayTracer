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
			src/Objects/Camera/Camera.cpp
			src/Scene/Scene.cpp
			src/Objects/Sphere/Sphere.cpp)

	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
	target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIBRARY})
endfunction()

function(setupLinux)
	find_package(SDL2 REQUIRED)
	find_package(GLM REQUIRED)
	include_directories(${GLM_INCLUDE_DIRS})
	include_directories(${SDL2_INCLUDE_DIRS})
	include_directories(${PROJECT_SOURCE_DIR}/src)
	add_executable(RT
			src/main.cpp
			src/RayTracer/RayTracer.cpp
			src/Window/Window.cpp
			src/EventHandler/EventHandler.hpp
			src/EventHandler/EventHandler.cpp
			src/Scene/Scene.cpp
			src/Scene/Scene.hpp
			src/Objects/Sphere/Sphere.cpp
			src/Objects/Sphere/Sphere.hpp
			src/Objects/Camera/Camera.cpp
			src/Ray/Ray.hpp
			src/Ray/Ray.cpp
			)

	string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} pthread)
endfunction()

if (WIN32)
	setupWindows()
else (WIN32)
	setupLinux()
endif(WIN32)