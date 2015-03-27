cmake_minimum_required(VERSION 2.4)

project(Shooter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lallegro -lallegro_image -lallegro_primitives")

file(GLOB_RECURSE SOURCE_FILES
	src/*.cc src/*.h
)

add_executable(Shooter ${SOURCE_FILES})
