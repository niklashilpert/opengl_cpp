//
// Created by niklas on 30.01.25.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <string>

#include <GLFW/glfw3.h>

class Window;

typedef struct KeyCallback {
    Window &window;
    const int key;
    const int scancode;
    const int action;
    const int mods;
} KeyCallback;

class Window {
public:
    static void updateEvents();

    Window(int width, int height, const std::string &title);
    ~Window();
    void close() const;
    [[nodiscard]] bool should_close() const;
    [[nodiscard]] bool is_key_pressed(int key) const;
    void updateBuffers() const;

    void set_width(int width);
    void set_height(int height);
    void set_title(const std::string &title);
    [[nodiscard]] int get_width() const;
    [[nodiscard]] int get_height() const;
    [[nodiscard]] std::string get_title() const;
    [[nodiscard]] float get_aspect_ratio() const;

private:
    static int instance_count;
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    GLFWwindow *window;
    std::string title;
    int width, height;
};

#endif //WINDOW_H
