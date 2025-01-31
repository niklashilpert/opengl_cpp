cmake_minimum_required(VERSION 3.30)
project(GL)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lglfw)

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders/)

add_executable(GL
        main.cpp
        gl/Shader.cpp
        gl/Shader.h
        io/io.cpp
        io/io.h
        window/window.cpp
        window/window.h
        glad/glad.c
)

target_link_libraries(GL ${OpenGlLinkers})

