//
// Created by niklas on 2/10/25.
//

#ifndef CUBERENDERER_H
#define CUBERENDERER_H
#include <cstdio>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_geometric.hpp>

#include "Texture.h"
#include "TextureInstance.h"
#include "../window/window.h"

namespace gl {
    class Texture;
    class Shader;
}

inline void renderCube() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    const Window window(800, 640, "OpenGL - Test");

    auto cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    auto cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = normalize(cameraPos - cameraTarget);
    auto up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = cross(cameraDirection, cameraRight);
    auto cameraFront = glm::vec3(0, 0, -1);

    gl::Shader *shader = gl::loadTextureShader();
    gl::Texture *grass_texture = load_grass_block(shader);
    gl::Texture *debug_texture = load_debug_block(shader);

    std::vector<gl::TextureInstance> instances;

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 256; y++) {
            for (int z = 0; z < 16; z++) {
                instances.emplace_back(grass_texture, translate(glm::mat4(1.0f), glm::vec3(x, y, -z)));
            }
        }
    }

    double last_frame_time = glfwGetTime();
    float delta_time = 0.0;

    while (!window.should_close()) {

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto time = static_cast<float>(glfwGetTime());

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.get_aspect_ratio(), 0.1f, 1000.0f);
        shader->setMat4("projection", projection);

        auto view = glm::mat4(1.0f);
        /*view = translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        view = rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = rotate(view, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        view = rotate(view, time, glm::vec3(0, 1, 0));*/

        view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader->setMat4("view", view);

        for (auto instance : instances) {
            instance.draw();
        }

        std::cout << round((glfwGetTime() - time) * 1000) / 1000 << "ms\n";

        window.updateBuffers();

        const double current_frame_time = glfwGetTime();
        delta_time = static_cast<float>(current_frame_time - last_frame_time);
        last_frame_time = current_frame_time;

        constexpr float camera_speed = 6.0f;
        if (window.is_key_pressed(GLFW_KEY_W)) {
            cameraPos += camera_speed * cameraFront * delta_time;
        }
        if (window.is_key_pressed(GLFW_KEY_S)) {
            cameraPos -= camera_speed * cameraFront * delta_time;
        }
        if (window.is_key_pressed(GLFW_KEY_D)) {
            cameraPos += camera_speed * cameraRight * delta_time;
        }
        if (window.is_key_pressed(GLFW_KEY_A)) {
            cameraPos -= camera_speed * cameraRight * delta_time;
        }
        if (window.is_key_pressed(GLFW_KEY_Q)) {
            cameraPos -= camera_speed * cameraUp * delta_time;
        }
        if (window.is_key_pressed(GLFW_KEY_E)) {
            cameraPos += camera_speed * cameraUp * delta_time;
        }

        Window::updateEvents();
    }

    delete grass_texture;
    delete shader;

}

#endif //CUBERENDERER_H
