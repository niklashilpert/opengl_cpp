cmake_minimum_required(VERSION 3.30)
project(GL)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGLU -lGL -lglfw)

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)


add_executable(GL
        main.cpp
        glad/glad.c
        io/stb_image.h
        io/io.cpp
        io/io.h
        window/window.cpp
        window/window.h
        gl/Shader.cpp
        gl/Shader.h
        gl/Texture.h
        gl/Texture.cpp
        gl/Cube.cpp
        gl/Cube.h
        gl/TextureInstance.cpp
        gl/TextureInstance.h
)

target_link_libraries(GL ${OpenGlLinkers})

