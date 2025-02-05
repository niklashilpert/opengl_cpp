//
// Created by niklas on 30.01.25.
//

#include <glad/glad.h>

#include "window.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>


/* ###### STATIC ###### */

int Window::instance_count = 0;

void Window::updateEvents() {
    glfwPollEvents();
}


/* ###### MEMBERS ###### */

Window::Window(
    const int width,
    const int height,
    const std::string &title
): title(title),
   width(width),
   height(height) {
    if (instance_count == 0) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW3");
        }
    }

    instance_count++;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, const int w, const int h) {
        if (auto *window_pointer = static_cast<Window*>(glfwGetWindowUserPointer(window))) {
            window_pointer->framebuffer_size_callback(window, w, h);

        }
    });
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
}

Window::~Window() {
    close();
    glfwDestroyWindow(window);
    instance_count--;
    if (instance_count == 0) {
        glfwTerminate();
    }
}

void Window::close() const {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


bool Window::should_close() const {
    return glfwWindowShouldClose(window);
}

bool Window::is_key_pressed(const int key) const {
    return glfwGetKey(window, key) != GLFW_RELEASE;
}

void Window::updateBuffers() const {
    glfwSwapBuffers(window);
}


void Window::set_width(const int width) {
    this->width = width;
}
void Window::set_height(const int height) {
    this->height = height;
}
void Window::set_title(const std::string &title) {
    this->title = title;
}
int Window::get_width() const {
    return this->width;
}
int Window::get_height() const {
    return this->height;
}
float Window::get_aspect_ratio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}
std::string Window::get_title() const {
    return this->title;
}



void Window::error_callback(int error, const char *description) {
    throw std::runtime_error("GLFW error: " + std::string(description));
}

void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
    std::cout << "Framebuffer size: " << width << " x " << height << std::endl;
}


void Window::key_callback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

