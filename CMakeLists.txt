cmake_minimum_required(VERSION 2.4)

project(Shooter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB_RECURSE SOURCE_FILES
	src/*.cc src/*.h
)

add_executable(Shooter ${SOURCE_FILES})
target_link_libraries(Shooter 
	allegro
	allegro_acodec
	allegro_audio
	allegro_color
	allegro_dialog
	allegro_font
	allegro_image
	allegro_main
	allegro_memfile
	allegro_physfs
	allegro_primitives
	allegro_ttf
)