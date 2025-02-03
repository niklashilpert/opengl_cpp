//
// Created by niklas on 30.01.25.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

GLFWwindow* create_window(int width, int height, const std::string &title);

inline int window_width;
inline int window_height;

#endif //WINDOW_H
