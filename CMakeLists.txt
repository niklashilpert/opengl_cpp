cmake_minimum_required(VERSION 3.30)
project(GL)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lglfw)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.vert ${CMAKE_CURRENT_BINARY_DIR}/shaders/shader.vert COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_orange.frag ${CMAKE_CURRENT_BINARY_DIR}/shaders/shader_orange.frag COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader_yellow.frag ${CMAKE_CURRENT_BINARY_DIR}/shaders/shader_yellow.frag COPYONLY)

add_executable(GL main.cpp glad/glad.c gl/gl.h gl/gl.cpp io/io.h io/io.cpp window/window.h window/window.cpp)

target_link_libraries(GL ${OpenGlLinkers})

