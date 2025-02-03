//
// Created by niklas on 02.02.25.
//

#include "Cube.h"

#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>
#include <utility>

const std::vector front_vertices{
    Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(1, 0)},
    Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(0, 0)},
};

const std::vector left_vertices{
    Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(1, 0)},
    Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(0, 0)},
};

const std::vector top_vertices{
    Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(-.5f, .5f, .5f), glm::vec2(1, 0)},
    Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(0, 0)},
};

const std::vector back_vertices{
    Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(-.5f, .5f, -.5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(0, 0)},
    Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(1, 0)},
};

const std::vector right_vertices{
    Vertex{glm::vec3(.5f, .5f, .5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(.5f, .5f, -.5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(0, 0)},
    Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(1, 0)},
};

const std::vector bottom_vertices{
    Vertex{glm::vec3(.5f, -.5f, .5f), glm::vec2(0, 1)},
    Vertex{glm::vec3(.5f, -.5f, -.5f), glm::vec2(1, 1)},
    Vertex{glm::vec3(-.5f, -.5f, .5f), glm::vec2(0, 0)},
    Vertex{glm::vec3(-.5f, -.5f, -.5f), glm::vec2(1, 0)},
};

const std::vector<unsigned int> indices = {
    0, 1, 3,
    0, 2, 3,
};

std::vector<Vertex> get_front_texture(const std::string &file_path, glm::mat4 &transform) {

}



typedef struct TexturePos {
    glm::vec3 position;
    Texture texture;
} TexturePos;

Cube::Cube(
    const glm::mat4 &transform,
    Texture *texture_front,
    Texture *texture_back,
    Texture *texture_left,
    Texture *texture_right,
    Texture *texture_top,
    Texture *texture_bottom
) : texture_front(texture_front),
    texture_back(texture_back),
    texture_left(texture_left),
    texture_right(texture_right),
    texture_top(texture_top),
    texture_bottom(texture_bottom) {
    transform_cube(transform, false);
}

Cube::~Cube() {
    delete texture_front;
    delete texture_back;
    delete texture_left;
    delete texture_right;
    delete texture_top;
    delete texture_bottom;
}

void Cube::transform_cube(const glm::mat4 &transform, const bool relative) {
    texture_front->transform_texture(transform, relative);
    texture_back->transform_texture(transform, relative);
    texture_left->transform_texture(transform, relative);
    texture_right->transform_texture(transform, relative);
    texture_top->transform_texture(transform, relative);
    texture_bottom->transform_texture(transform, relative);
}


void Cube::draw() const {
    texture_front->draw();
    texture_back->draw();
    texture_left->draw();
    texture_right->draw();
    texture_top->draw();
    texture_bottom->draw();
}

Cube make_grass(const glm::mat4 &transform) {
    auto *front = new Texture(TextureInfo (GRASS_SIDE_PATH, front_vertices, indices), transform);
    auto *back = new Texture(TextureInfo (GRASS_SIDE_PATH, back_vertices, indices), transform);
    auto *left = new Texture(TextureInfo (GRASS_SIDE_PATH, left_vertices, indices), transform);
    auto *right = new Texture(TextureInfo (GRASS_SIDE_PATH, right_vertices, indices), transform);
    auto *top = new Texture(TextureInfo (GRASS_TOP_PATH, top_vertices, indices), transform);
    auto *bottom = new Texture(TextureInfo (GRASS_BOTTOM_PATH, bottom_vertices, indices), transform);
    return Cube(transform, front, back, left, right, top, bottom);
}

Cube make_default(const glm::mat4 &transform) {
    auto *front = new Texture(TextureInfo (DEFAULT_CUBE_PATH, front_vertices, indices), transform);
    auto *back = new Texture(TextureInfo (DEFAULT_CUBE_PATH, back_vertices, indices), transform);
    auto *left = new Texture(TextureInfo (DEFAULT_CUBE_PATH, left_vertices, indices), transform);
    auto *right = new Texture(TextureInfo (DEFAULT_CUBE_PATH, right_vertices, indices), transform);
    auto *top = new Texture(TextureInfo (DEFAULT_CUBE_PATH, top_vertices, indices), transform);
    auto *bottom = new Texture(TextureInfo (DEFAULT_CUBE_PATH, bottom_vertices, indices), transform);
    return Cube(transform, front, back, left, right, top, bottom);
}

Cube make_brick(const glm::mat4 &transform) {
    auto *front = new Texture(TextureInfo (BRICK_PATH, front_vertices, indices), transform);
    auto *back = new Texture(TextureInfo (BRICK_PATH, back_vertices, indices), transform);
    auto *left = new Texture(TextureInfo (BRICK_PATH, left_vertices, indices), transform);
    auto *right = new Texture(TextureInfo (BRICK_PATH, right_vertices, indices), transform);
    auto *top = new Texture(TextureInfo (BRICK_PATH, top_vertices, indices), transform);
    auto *bottom = new Texture(TextureInfo (BRICK_PATH, bottom_vertices, indices), transform);
    return Cube(transform, front, back, left, right, top, bottom);
}

