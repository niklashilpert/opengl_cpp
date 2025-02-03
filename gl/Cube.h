//
// Created by niklas on 02.02.25.
//

#ifndef CUBE_H
#define CUBE_H
#include "Texture.h"

const std::string GRASS_TOP_PATH = "resources/textures/grass/top.png";
const std::string GRASS_SIDE_PATH = "resources/textures/grass/side.png";
const std::string GRASS_BOTTOM_PATH = "resources/textures/grass/bottom.png";

const std::string DEFAULT_CUBE_PATH = "resources/textures/default/default.png";

const std::string BRICK_PATH = "resources/textures/wall.png";

class Cube {
public:
    Texture *texture_front;
    Texture *texture_back;
    Texture *texture_left;
    Texture *texture_right;
    Texture *texture_top;
    Texture *texture_bottom;

    explicit Cube(
        const glm::mat4 &transform,
        Texture *texture_front,
        Texture *texture_back,
        Texture *texture_left,
        Texture *texture_right,
        Texture *texture_top,
        Texture *texture_bottom
    );

    ~Cube();

    void transform_cube(const glm::mat4 &transform, bool relative);

    void draw() const;
};

Cube make_grass(const glm::mat4 &transform);

Cube make_default(const glm::mat4 &transform);

Cube make_brick(const glm::mat4 &transform);

#endif //CUBE_H
